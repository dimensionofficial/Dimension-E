/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <asserter/asserter.hpp> /// defines assert_def struct (abi)

using namespace asserter;

static int global_variable = 45;

extern "C" {
    /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t /* receiver */, uint64_t code, uint64_t action ) {
       require_auth(code);
       if( code == N(asserter) ) {
          if( action == N(procassert) ) {
             assertdef def = eosio::unpack_action_data<assertdef>();

             // maybe assert?
             eosio_assert((uint32_t)def.condition, def.message.c_str());
          } else if( action == N(provereset) ) {
             eosio_assert(global_variable == 45, "Global Variable Initialized poorly");
             global_variable = 100;
          }
       }
    }
}
// updated at 7.5
/**
 *  @dev minakokojima, yukiexe
 *  @copyright Andoromeda
 */
#pragma once
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
// #include <eosiolib/currency.hpp>
// #include <eosiolib/singleton.hpp>
#include <eosiolib/transaction.hpp>

#include "council.hpp"
#include "NFT.hpp"
// #include <cmath>
// #include <string>

#include "config.hpp"
#include "utils.hpp"
#include "kyubey.hpp"
// #include "eosio.token.hpp"
 
typedef double real_type;

using std::string;
using eosio::symbol_name;
using eosio::asset;
using eosio::symbol_type;
using eosio::permission_level;
using eosio::action;
using eosio::extended_asset;
using eosio::unpack_action_data;

class cryptomeetup : public council {
    public: cryptomeetup(account_name self) :
        council(self),
        _global(_self, _self),
        _market(_self, _self),
        _land(_self, _self){}

    // @abi action
    void init();
    // @abi action
    void clear();     
    // @abi action
    void test();
    // @abi action
    void unstake(account_name from, uint64_t amount);
    // @abi action
    void claim(account_name from);    

    // @abi action
    void transfer(account_name   from,
                  account_name   to,
                  asset          quantity,
                  string         memo);
    
    void onTransfer(account_name from, account_name to,
                    extended_asset quantity, string memo); 

    // @abi action
    void newland(account_name &from, asset &eos);
    // @abi action
    void airdrop(account_name to, uint64_t amount);
    // @abi action
    void checkin(account_name from, const checksum256 &hash);

    void buy_land(account_name from, extended_asset in, const vector<string>& params);
    void buy(account_name from, extended_asset in, const vector<string>& params);
    void sell(account_name from, extended_asset in, const vector<string>& params);    


    void apply(account_name code, action_name action);

    // @abi table land
    struct land {
        uint64_t     id;
        account_name owner = 0;
        uint64_t primary_key()const { return id; }        
        uint64_t price;           
        uint64_t parent;
        void tax() {
        }
        uint64_t next_price() const {
            return price * 1.35;
        }
    };    
    /*
    struct land : public NFT::tradeable_token {
        uint64_t parent;
        void tax() {
        }
        uint64_t next_price() const {
            return price * 1.35;
        }
    };*/
    
    // @abi table players
    struct player_info {
        uint64_t land_profit;
        uint64_t ref_profit;
        uint64_t fee_profit;
        uint64_t pool_profit;
        uint64_t staked_income;
        uint64_t council_income;
    };

    // @abi table checkins
    struct checkin_info {
        uint64_t event_id;
        uint64_t primary_key()const { return event_id; }        
    };
        
    // @abi table global
    struct global {       
        uint64_t team;
        uint64_t pool;
        uint64_t defer_id;
        uint64_t total_staked;
        account_name last;
        time st, ed;
    };

    typedef eosio::multi_index<N(checkins), checkin_info> checkin_index;

    typedef eosio::multi_index<N(land), land> land_index;
    land_index _land;

    typedef eosio::multi_index<N(market), kyubey::market> market_index;
    market_index _market;    

    typedef singleton<N(global), global> singleton_global;
    singleton_global _global;     

    typedef singleton<N(players), player_info> singleton_players;  
    
    // @abi action
    void receipt(const rec_reveal& reveal) {
        require_auth(_self);
    }

    uint64_t get_next_defer_id() {
        auto g = _global.get();    
        g.defer_id += 10;
        _global.set(g, _self);
        return g.defer_id;
    }

    template <typename... Args>
    void send_defer_action(Args&&... args) {
        transaction trx;
        trx.actions.emplace_back(std::forward<Args>(args)...);
        trx.send(get_next_defer_id(), _self, false);
    }
};



void cryptomeetup::apply(account_name code, action_name action) {   
    auto &thiscontract = *this;

    if (action == N(transfer)) {
        auto transfer_data = unpack_action_data<st_transfer>();
        // onTransfer(transfer_data.from, transfer_data.to, extended_asset(transfer_data.quantity, code), transfer_data.memo);    
        return;
    }

    if (code != _self) return;
    switch (action) {
        EOSIO_API(cryptomeetup, (init)(newland));
        //EOSIO_API(cryptomeetup, (init)(newland)(airdrop)(unstake)(claim)(checkin));
    };
}

extern "C" {
    [[noreturn]] void apply(uint64_t receiver, uint64_t code, uint64_t action) 
    {
        cryptomeetup p(receiver);
        p.apply(code, action);
        eosio_exit(0);
    }
}

