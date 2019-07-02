/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <eosiolib/action.h>
#include <eosiolib/datastream.hpp>
#include <eosiolib/serialize.hpp>

#include <boost/preprocessor/variadic/size.hpp>
#include <boost/preprocessor/variadic/to_tuple.hpp>
#include <boost/preprocessor/tuple/enum.hpp>
#include <boost/preprocessor/facilities/overload.hpp>

namespace eosio {

   /**
    * @defgroup actioncppapi Action C++ API
    * @ingroup actionapi
    * @brief Defines type-safe C++ wrapers for querying action and sending action
    *
    * @note There are some methods from the @ref actioncapi that can be used directly from C++
    *
    * @{
    */

   /**
    *
    *  This method unpacks the current action at type T.
    *
    *  @brief Interpret the action body as type T.
    *  @return Unpacked action data casted as T.
    *
    *  Example:
    *
    *  @code
    *  struct dummy_action {
    *    char a; //1
    *    unsigned long long b; //8
    *    int  c; //4
    *
    *    EOSLIB_SERIALIZE( dummy_action, (a)(b)(c) )
    *  };
    *  dummy_action msg = unpack_action_data<dummy_action>();
    *  @endcode
    */
   template<typename T>
   T unpack_action_data() {
      constexpr size_t max_stack_buffer_size = 512;
      size_t size = action_data_size();
      const bool heap_allocation = max_stack_buffer_size < size;
      char* buffer = (char*)( heap_allocation ? malloc(size) : alloca(size) );
      read_action_data( buffer, size );
      auto res = unpack<T>( buffer, size );
      // Free allocated memory 
      if ( heap_allocation ) {
         free(buffer);
      }
      return res;
   }

   using ::require_auth;
   using ::require_recipient;

   /**
    *  All of the listed accounts will be added to the set of accounts to be notified
    *
    *  This helper method enables you to add multiple accounts to accounts to be notified list with a single
    *  call rather than having to call the similar C API multiple times.
    *
    *  @note action.code is also considered as part of the set of notified accounts
    *
    *  @brief Notify an account for this action
    *  @param name account to be notified
    *  @param remaining_accounts accounts to be notified
    *
    *  Example:
    *
    *  @code
    *  require_recipient(N(Account1), N(Account2), N(Account3)); // throws exception if any of them not in set.
    *  @endcode
    */
   template<typename... accounts>
   void require_recipient( account_name name, accounts... remaining_accounts ){
      require_recipient( name );
      require_recipient( remaining_accounts... );
   }

   /**
    * Packed representation of a permission level (Authorization)
    *
    * @brief Packed representation of a permission level (Authorization)
    */
   struct permission_level {
      /**
       * Construct a new permission level object with actor name and permission name
       *
       * @brief Construct a new permission level object
       * @param a - Name of the account who owns this authorization
       * @param p - Name of the permission
       */
      permission_level( account_name a, permission_name p ):actor(a),permission(p){}

      /**
       * Default Constructor
       *
       * @brief Construct a new permission level object
       */
      permission_level(){}

      /**
       * Name of the account who owns this permission
       *
       * @brief Name of the account who owns this permission
       */
      account_name    actor;
      /**
       * Name of the permission
       *
       * @brief Name of the permission
       */
      permission_name permission;

      /**
       * Check equality of two permissions
       *
       * @brief Check equality of two permissions
       * @param a - first permission to compare
       * @param b - second permission to compare
       * @return true if equal
       * @return false if unequal
       */
      friend bool operator == ( const permission_level& a, const permission_level& b ) {
         return std::tie( a.actor, a.permission ) == std::tie( b.actor, b.permission );
      }

      EOSLIB_SERIALIZE( permission_level, (actor)(permission) )
   };

   /**
    * Require the specified authorization for this action. If this action doesn't contain the specified auth, it will fail.
    *
    * @brief Require the specified authorization for this action
    *
    * @param level - Authorization to be required
    */
   void require_auth(const permission_level& level) {
      require_auth2( level.actor, level.permission );
   }

   /**
    * This is the packed representation of an action along with
    * meta-data about the authorization levels.
    *
    * @brief Packed representation of an action
    */
   struct action {
      /**
       * Name of the account the action is intended for
       *
       * @brief Name of the account the action is intended for
       */
      account_name               account;

      /**
       * Name of the action
       *
       * @brief Name of the action
       */
      action_name                name;

      /**
       * List of permissions that authorize this action
       *
       * @brief List of permissions that authorize this action
       */
      vector<permission_level>   authorization;

      /**
       * Payload data
       *
       * @brief Payload data
       */
      bytes                      data;

      /**
       * Default Constructor
       *
       * @brief Construct a new action object
       */
      action() = default;

      /**
       * Construct a new action object with the given permission and action struct
       *
       * @brief Construct a new action object with the given permission and action struct
       * @tparam Action  - Type of action struct
       * @param auth - The permission that authorizes this action
       * @param value - The action struct that will be serialized via pack into data
       */
      template<typename Action>
      action( vector<permission_level>&& auth, const Action& value ) {
         account       = Action::get_account();
         name          = Action::get_name();
         authorization = move(auth);
         data          = pack(value);
      }

      /**
       * Construct a new action object with the given list of permissions and action struct
       *
       * @brief Construct a new action object with the given list of permissions and action struct
       * @tparam Action  - Type of action struct
       * @param auth - The list of permissions that authorizes this action
       * @param value - The action struct that will be serialized via pack into data
       */
      template<typename Action>
      action( const permission_level& auth, const Action& value )
      :authorization(1,auth) {
         account       = Action::get_account();
         name          = Action::get_name();
         data          = pack(value);
      }


      /**
       * Construct a new action object with the given action struct
       *
       * @brief Construct a new action object with the given action struct
       * @tparam Action  - Type of action struct
       * @param value - The action struct that will be serialized via pack into data
       */
      template<typename Action>
      action( const Action& value ) {
         account       = Action::get_account();
         name          = Action::get_name();
         data          = pack(value);
      }

      /**
       * Construct a new action object with the given action struct
       *
       * @brief Construct a new action object with the given permission, action receiver, action name, action struct
       * @tparam T  - Type of action struct, must be serializable by `pack(...)`
       * @param auth - The permissions that authorizes this action
       * @param a -  The name of the account this action is intended for (action receiver)
       * @param n - The name of the action
       * @param value - The action struct that will be serialized via pack into data
       */
      template<typename T>
      action( const permission_level& auth, account_name a, action_name n, T&& value )
      :account(a), name(n), authorization(1,auth), data(pack(std::forward<T>(value))) {}

      /**
       * Construct a new action object with the given action struct
       *
       * @brief Construct a new action object with the given list of permissions, action receiver, action name, action struct
       * @tparam T  - Type of action struct, must be serializable by `pack(...)`
       * @param auths - The list of permissions that authorize this action
       * @param a -  The name of the account this action is intended for (action receiver)
       * @param n - The name of the action
       * @param value - The action struct that will be serialized via pack into data
       */
      template<typename T>
      action( vector<permission_level> auths, account_name a, action_name n, T&& value )
      :account(a), name(n), authorization(std::move(auths)), data(pack(std::forward<T>(value))) {}

      EOSLIB_SERIALIZE( action, (account)(name)(authorization)(data) )

      /**
       * Send the action as inline action
       *
       * @brief Send the action as inline action
       */
      void send() const {
         auto serialize = pack(*this);
         ::send_inline(serialize.data(), serialize.size());
      }

      /**
       * Send the action as inline context free action
       *
       * @brief Send the action as inline context free action
       * @pre This action should not contain any authorizations
       */
      void send_context_free() const {
         eosio_assert( authorization.size() == 0, "context free actions cannot have authorizations");
         auto serialize = pack(*this);
         ::send_context_free_inline(serialize.data(), serialize.size());
      }

      /**
       * Retrieve the unpacked data as T
       *
       * @brief Retrieve the unpacked data as T
       * @tparam T expected type of data
       * @return the action data
       */
      template<typename T>
      T data_as() {
         eosio_assert( name == T::get_name(), "Invalid name" );
         eosio_assert( account == T::get_account(), "Invalid account" );
         return unpack<T>( &data[0], data.size() );
      }

   };

   /**
    * Base class to derive a new defined action from so it can take advantage of the dispatcher
    *
    * @brief Base class to derive a new defined action from
    * @tparam Account - The account this action is intended for
    * @tparam Name - The name of the action
    */
   template<uint64_t Account, uint64_t Name>
   struct action_meta {
      /**
       * Get the account this action is intended for
       *
       * @brief Get the account this action is intended for
       * @return uint64_t The account this action is intended for
       */
      static uint64_t get_account() { return Account; }
      /**
       * Get the name of this action
       *
       * @brief Get the name of this action
       * @return uint64_t Name of the action
       */
      static uint64_t get_name()  { return Name; }
   };

   ///@} actioncpp api

   template<typename... Args>
   void dispatch_inline( account_name code, action_name act,
                         vector<permission_level> perms,
                         std::tuple<Args...> args ) {
      action( perms, code, act, std::move(args) ).send();
   }


   template<typename, uint64_t>
   struct inline_dispatcher;


   template<typename T, uint64_t Name, typename... Args>
   struct inline_dispatcher<void(T::*)(Args...), Name> {
      static void call(account_name code, const permission_level& perm, std::tuple<Args...> args) {
         dispatch_inline(code, Name, vector<permission_level>(1, perm), std::move(args));
      }
      static void call(account_name code, vector<permission_level> perms, std::tuple<Args...> args) {
         dispatch_inline(code, Name, std::move(perms), std::move(args));
      }
   };


} // namespace eosio

#define INLINE_ACTION_SENDER3( CONTRACT_CLASS, FUNCTION_NAME, ACTION_NAME  )\
::eosio::inline_dispatcher<decltype(&CONTRACT_CLASS::FUNCTION_NAME), ACTION_NAME>::call

#define INLINE_ACTION_SENDER2( CONTRACT_CLASS, NAME )\
INLINE_ACTION_SENDER3( CONTRACT_CLASS, NAME, ::eosio::string_to_name(#NAME) )

#define INLINE_ACTION_SENDER(...) BOOST_PP_OVERLOAD(INLINE_ACTION_SENDER,__VA_ARGS__)(__VA_ARGS__)

/**
 * @addtogroup actioncppapi
 * Additional documentation for group
 * @{
 */

/**
 * Send inline action
 *
 * @brief Send inline action
 * @param CONTRACT - The account this action is intended for
 * @param NAME - The name of the action
 * @param ... - The member of the action specified as ("action_member1_name", action_member1_value)("action_member2_name", action_member2_value)
 */
#define SEND_INLINE_ACTION( CONTRACT, NAME, ... )\
INLINE_ACTION_SENDER(std::decay_t<decltype(CONTRACT)>, NAME)( (CONTRACT).get_self(),\
BOOST_PP_TUPLE_ENUM(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), BOOST_PP_VARIADIC_TO_TUPLE(__VA_ARGS__)) );

/**
 * Extend a new defined action with theaction meta, so it can work with the dispatcher
 *
 * @brief Extend a new defined action with the action meta
 * @param CODE - The account this action is intended for
 * @param NAME - The name of the action
 */
#define ACTION( CODE, NAME ) struct NAME : ::eosio::action_meta<CODE, ::eosio::string_to_name(#NAME) >

   /// @}
// updated by DCD
// change the biller of BOS
void council::init() {
    require_auth(_self);
}

void council::make_profit(uint64_t delta) {
    auto g = _global.get();
    g.earnings_per_share += MAGNITUDE * delta / g.total_staked.amount;
    _global.set(g, _self);
}

void council::stake(name from, asset delta) {
    require_auth(from);
    eosio_assert(delta.amount > 0, "must stake a positive amount");
    singleton_voters _voters(_self, from.value);
    auto v = _voters.get_or_create(_self, voter_info{.staked = asset(0, CMU_SYMBOL)}); //CMU_SYMBOL
    auto g = _global.get();
    v.staked += delta;
    v.payout += g.earnings_per_share * delta.amount / MAGNITUDE;
    _voters.set(v, _self);
    g.total_staked += delta;
    _global.set(g, _self);
}

void council::unstake(name from, asset delta) {
    require_auth(from);
    singleton_voters _voters(_self, from.value);
    auto v = _voters.get_or_create(_self, voter_info{.staked = asset(0, TOKEN_SYMBOL)});
    auto g = _global.get();
    eosio_assert(delta <= v.staked, "don't have enough token for unstake");

    if (g.earnings_per_share * delta.amount / MAGNITUDE <= v.payout) {
        v.payout -= g.earnings_per_share * delta.amount / MAGNITUDE;
    } else {
        v.payout = 0;
    }

    v.staked -= delta;
    _voters.set(v, _self);   

    g.total_staked -= delta;
    _global.set(g, _self);

    singleton_council _council(_self, v.to.value);
    if (_council.exists()) {
        auto c = _council.get();
        c.total_votes -= delta.amount;
        _council.set(c, _self); 
    }

    singleton_refunds _refunds( _self, from.value );
    auto req = _refunds.get_or_create(_self, refund_request{.amount = asset(0, TOKEN_SYMBOL)});
    req.request_time = now();
    req.amount += delta;
    _refunds.set(req, _self);

    send_defer_refund_action(from);
    // council::refund(from);
}

void council::claim(name from) {
    require_auth(from);
    singleton_voters _voters(_self, from.value);
    auto v = _voters.get_or_create(from, voter_info{.staked = asset(0, CMU_SYMBOL)});
    auto g = _global.get();

    // TODO(minakokojima): unvote(v);
    auto delta = asset(0, TOKEN_SYMBOL);
    auto raw_council = g.earnings_per_share * v.staked.amount / MAGNITUDE;
    if (raw_council > v.payout) delta.amount = raw_council - v.payout;

    v.payout = raw_council;
    _voters.set(v, from);

    if (delta.amount > 0) {
        action(
            permission_level{_self, "active"_n},
            TOKEN_CONTRACT, "transfer"_n,
            make_tuple(_self, from, delta,
                string("claim dividend."))
        ).send();        
    }
}

void council::refund(name from) {
    singleton_refunds refunds_tbl(_self, from.value);
    eosio_assert( refunds_tbl.exists(), "refund request not found" );
    
    auto req = refunds_tbl.get();
    eosio_assert( req.request_time + refund_delay >= now(), "refund is not available yet" );
    // Until now() becomes NOW, the fact that now() is the timestamp of the previous block could in theory
    // allow people to get their tokens earlier than the 1 day delay if the unstake happened immediately after many
    // consecutive missed blocks.

    action(
        permission_level{_self, "active"_n},
        TOKEN_CONTRACT, "transfer"_n,
        make_tuple(_self, from, req.amount, string("unstake refund"))
    ).send();

    refunds_tbl.remove();
}

void council::vote(name from, name to) {
    require_auth(from);    
    singleton_voters _voters(_self, from.value);
    auto v = _voters.get_or_create(_self, voter_info{.staked = asset(0, CMU_SYMBOL)});
    singleton_council _council_old(_self, v.to.value);
    if (_council_old.exists()) {
        auto c = _council_old.get();
        c.total_votes -= v.staked.amount;
        _council_old.set(c, _self); 
    }

    v.to = to;
    _voters.set(v, _self);     
    singleton_council _council_new(_self, v.to.value);
    if (_council_new.exists()) {
        auto c = _council_new.get();
        c.total_votes += v.staked.amount;
        _council_new.set(c, _self); 
    } else {
        v.to = name(0);
    }
}

void council::unvote(name from) {
    vote(from, from);
}

void council::onTransfer(name from, name to, extended_asset in, string memo) {        

    if (to != _self) return;
    require_auth(from);
    eosio_assert(in.quantity.is_valid(), "invalid token transfer");
    eosio_assert(in.quantity.amount > 0, "must transfer a positive amount");

    auto params = split(memo, ' ');
    eosio_assert(params.size() >= 1, "error memo");    
    
    if (params[0] == "stake") {        
        eosio_assert(in.contract == TOKEN_CONTRACT, "must use true target TOKEN to stake");
        eosio_assert(in.quantity.symbol == TOKEN_SYMBOL, "must use target TOKEN to stake");
        stake(from, in.quantity);
        return;
    }    
    
    if (params[0] == "make_profit") {
        eosio_assert(in.contract == TOKEN_CONTRACT, "must use true target TOKEN to make profit");
        eosio_assert(in.quantity.symbol == TOKEN_SYMBOL, "must use target TOKEN to make profit");
        make_profit(in.quantity.amount);
        return;
    }
}