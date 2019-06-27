#pragma once
namespace bancor {
   template<typename ConverterCurrency, typename FirstCurrency, typename SecondCurrency>
   class converter_contract {
      public:
         typedef ConverterCurrency   converter_currency;
         typedef FirstCurrency       first_currency;
         typedef SecondCurrency      second_currency;


         static const account_name   converter_account = converter_currency::code;

         struct converter_state {
            typename converter_currency::token_type supply; /// total supply held by all users
            typename converter_currency::token_type balance; /// supply held by converter in its own balance
         };

         struct converter_args {
            eosio::account_name    to_currency_account;
            eosio::symbol_name     to_currency_symbol;
            uint64_t               min_return_currency;
         };


         template<typename CurrencyType, uint32_t Weight=500000, uint32_t Base=1000000> 
         struct connector {
            typedef CurrencyType                            currency_type;
            typedef typename converter_currency::token_type converter_token_type;
            typedef typename currency_type::token_type      in_token_type;

            converter_token_type convert_to_converter( in_token_type in, converter_state& state ) {
               in_token_type balance = currency_type::get_balance( converter_account );

               /// balance already changed when transfer executed, get pre-transfer balance
               in_token_type previous_balance = balance - in; 

               auto init_price = (previous_balance * Base) / (Weight * state.supply);
               auto init_out   = init_price * in;

               auto out_price  = (balance*Base) / (Weight * (state.supply+init_out) );
               auto final_out  = out_price * in;

               state.balance += final_out;
               state.supply  += final_out;

               return final_out;
            }


            in_token_type convert_from_converter( converter_token_type converter_in, converter_state& state ) {
               in_token_type  to_balance = CurrencyType::get_balance( converter_account );

               auto          init_price = (to_balance * Base) / (Weight * state.supply);
               in_token_type init_out   = init_price * converter_in;

               state.supply  -= converter_in;
               state.balance -= converter_in;

               auto out_price  = ((to_balance-init_out) * Base) / ( Weight * (state.supply) );

               return out_price * converter_in;
            }

         };



         /**
          * This is called when we receive RELAY tokens from user and wish to
          * convert to one of the connector currencies.
          */
         static void on_convert( const typename converter_currency::transfer& trans, 
                                       const converter_args& args, 
                                       converter_state& state ) {

            if( args.to_currency_type == first_currency ) {
               auto output = first_connector::convert_from_converter( trans.quantity, state );
               save_and_send( trans.from, state, output, args.min_return );
            }
            else if( args.to_currency_type == second_currency ) {
               auto output = second_connector::convert_from_converter( trans.quantity, state );
               save_and_send( trans.from, state, output, args.min_return );
            } 
            else {
               eosio_assert( false, "invalid to currency" );
            }
         }


         /**
          *  This is called when the converter receives one of the connector currencies and it 
          *  will send either converter tokens or a different connector currency in response.
          */
         template<typename ConnectorType>
         static void on_convert( const typename ConnectorType::currency_type::transfer& trans,
                                       const converter_args& args, 
                                       converter_state& state ) 
         {
            /// convert to converter
            auto converter_out = ConnectorType::convert_to_converter( trans.quantity, state );

            if( args.to_currency_type == converter_currency )
            {
               save_and_send( trans.from, state, converter_out, args.min_return );
            }
            else 
            {
               auto output = ConnectorType::convert_from_converter( converter_out, state ); 
               save_and_send( trans.from, state, output, args.min_return );
            }
         }


         /**
          *  This method factors out the boiler plate for parsing args and loading the
          *  initial state before dispatching to the proper on_convert case
          */
         template<typename CurrencyType>
         static void start_convert( const typename CurrencyType::transfer_memo& trans ) {
            auto args = unpack<converter_args>( trans.memo );
            eosio_assert( args.to_currency_type != trans.quantity.token_type(), "cannot convert to self" );

            auto state = read_converter_state();
            on_convert( trans, args, state );
         }


         /**
          * converter_account first needs to call the currency handler to perform
          * user-to-user transfers of the converter token, then if a transfer is sending
          * the token back to the converter contract, it should convert like everything else.
          *
          *  This method should be called from apply( code, action ) for each of the
          *  transfer types that we support (for each currency)
          */
         static void on( const typename converter_currency::transfer_memo& trans ) {
            converter_currency::on( trans );
            if( trans.to == converter_account ) {
               start_convert( trans );
            }
         }

         /**
          *  All other currencies simply call start_convert if to == converter_account
          */
         template<typename Currency>
         static void on( const typename Currency::transfer_memo& trans ) {
            if( trans.to == converter_account ) {
               start_convert( trans );
            } else {
               eosio_assert( trans.from == converter_account, 
                       "received unexpected notification of transfer" );
            }
         }

         static void apply( account_name code, action_name action ) {
            if( !dispatch( converter_contract, 
                           converter_currency::transfer,
                           converter_currency::issue,
                           first_currency::transfer,
                           second_currency::transfer ) {
               eosio_assert( false, "received unexpected action" );
            }
         }
   }; /// converter_contract
} /// namespace bancor


class council : public eosio::contract {
    public: council(account_name self) :
        contract(self){}

    // @abi table voters
    struct voter_info {
        account_name to = 0;
        uint64_t     staked = 0;
    };       

    // @abi table proxies
    struct proxy_info {
        account_name to = 0;
        uint64_t delegated_staked = 0;
    };

    // @abi table council
    struct council_info {
        uint64_t     total_votes = 0;
        uint64_t     claimed     = 0;          // Dividends received
    };          

    typedef singleton<N(voters),  voter_info>  singleton_voters;
    typedef singleton<N(proxies), proxy_info>  singleton_proxies;
    typedef singleton<N(council), council_info>  singleton_council;   
//    singleton_voters _voters;
  //  singleton_proxies _proxies;
   // singleton_council _council;
    
    void stake(account_name from, uint64_t delta) {
        require_auth(from);
        eosio_assert(delta > 0, "must stake a positive amount");
        singleton_voters _voters(_self, from);
        auto v = _voters.get_or_create(_self, voter_info{});
        v.staked += delta;
        _voters.set(v, _self);
    }
    
    void unstake(account_name from, uint64_t amount) {
        require_auth(from);
        singleton_voters _voters(_self, from);
        auto v = _voters.get_or_create(_self, voter_info{});
        eosio_assert(amount <= v.staked, "don't have enough CMU for unstake");
        // TODO(minakokojima): unvote(v);

        action( // winner winner chicken dinner
            permission_level{_self, N(active)},
            N(dacincubator), N(transfer),
            make_tuple(_self, from, asset(amount, TOKEN_SYMBOL),
                std::string("transfer token by unstake"))
        ).send();
            
        v.staked -= amount;
        _voters.set(v, _self);
    }    
    /*
    void unvote(voters_table::const_iterator itr) {
    
        auto p = _proxies.find(itr->to);
        if (p != _proxies.end()) { 
            _proxies.modify(p, 0, [&](auto &pp) {
                pp.delegated_staked -= itr->staked;
            });
            auto c = _council.find(p->to);
            if (c != _council.end()) {                 
                _council.modify(c, 0, [&](auto &cc) {
                    cc.total_votes -= itr->staked;
                });     
            }
            return;
        }        
        auto c = _council.find(itr->to);
        if (c != _council.end()) {             
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes -= itr->staked;
            });
        }
        _voters.modify(itr, 0, [&](auto &v) {
        });
    }*/

     /*
    void unvote(proxies_table::const_iterator itr) {
   
        auto c = _council.find(itr->to);
        if (c != _council.end()) { 
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes -= itr->delegated_staked;
            });
        }
        
    }*/

    void unvote(account_name from) {
        /*
        require_auth(from);        
        auto v = _voters.find(from);
        if (v != _voters.end()) {
            unvote(v);
            return;
        }
        auto p = _proxies.find(from);
        if (p != _proxies.end()) {
            unvote(p);     
            return;
        }*/
    }
     /*
    void vote( voters::const_iterator itr) {
   
        unvote(itr);
        auto p = _proxies.find(itr->to);
        if (p != _proxies.end()) {             
            _proxies.modify(p, 0, [&](auto &pp) {
                pp.delegated_staked += itr->staked;
            });
            auto c = _council.find(p->to);
            if (c != _council.end()) { 
                _council.modify(c, 0, [&](auto &cc) {
                    cc.total_votes += itr->staked;
                });            
            }
            return;
        }        
        auto c = _council.find(itr->to);
        if (c != _council.end()) {             
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes += itr->staked;
            });
            return;          
        }
    }*/
  /* 
    void vote(proxies_table::const_iterator itr) {  
      
        unvote(itr);     
        auto c = _council.find(itr->to);
        if (c != _council.end()) { 
            _council.modify(c, 0, [&](auto &cc) {
                cc.total_votes += itr->delegated_staked;
            });
        }
    }    
    */
        /*   
    void vote(account_name from, account_name to) {   
  
        require_auth(from);
        auto v = _voters.find(from);
        if (v != _voters.end()) {                   
            _voters.modify(v, 0, [&](auto &vv) {
                vv.to = to;
            });    
            vote(v);
            return;
        }
        auto p = _proxies.find(from);
        if (p != _proxies.end()) {
            _voters.modify(v, 0, [&](auto &vv) {
                vv.to = to;
            });    
            vote(v);
            return;
        }
    }*/

    // Declare your participation in the agency
    void runproxy(account_name from) {
        /*
        require_auth(from);
        // warning!!!
        // What are the requirements for declaring an agent?
        // warning!!!
        auto itr_proxy = _proxies.find(from);
        eosio_assert(itr_proxy != _proxies.end(), "already be proxy");
        _proxies.emplace(_self, [&](auto &p) {
            p.owner = from;
        });
        // warning!!!
        // Type an event to let the front end know
        // warning!!!
    }    
    // Declare your participation in the committee
    void runcouncil(account_name from) {
        require_auth(from);
        // warning!!!
        // What are the requirements for becoming a committee?
        // warning!!!
        
        auto itr_council = _council.find(from);
        eosio_assert(itr_council != _council.end(), "already be council");
        _council.emplace(_self, [&](auto &c) {
            c.owner = from;
        });
        // warning!!!
        // Type an event to let the front end know
        // warning!!!
        */
    }

    // unstake Tokens can be retrieved after 72 hours
    void getToken(account_name from) {
        /*
        require_auth(from);        
        auto itr = _voters.find(from);
        eosio_assert(itr == _voters.end(), "this account didn't stake");        
        */
   }
};