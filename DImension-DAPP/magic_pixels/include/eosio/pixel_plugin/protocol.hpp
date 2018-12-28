
#pragma once

#include <eosio/chain/types.hpp>
#include <eosio/plugin_lib/plugin_lib.hpp>
#include <eosio/chain/action.hpp>
#include <regex>
#include <string>
#include <map>

#include <eosio/wallet_plugin/wallet_plugin.hpp>
#include <eosio/wallet_plugin/wallet_manager.hpp>
#include <fc/static_variant.hpp>
#include <fc/exception/exception.hpp>
#include <fc/variant.hpp>
#include <fc/io/json.hpp>
#include <fc/crypto/private_key.hpp>
#include <fc/crypto/public_key.hpp>


namespace {

 namespace ReplacementFor_pixel_message_t {
   struct init{};
   struct ReplacementFor_refresh{};
   struct ReplacementFor_changedur{};
   struct end{};
   struct ReplacementFor_createacct{};
   struct ReplacementFor_withdraw{};
   struct ReplacementFor_clearpixels{};
   struct ReplacementFor_clearaccts{};
   struct ReplacementFor_clearcanvs{};
   struct ReplacementFor_resetquota{};
   struct ReplacementFor_dump_tables{};
   struct ReplacementFor_transfer{};
   struct ReplacementFor_create_system_acct{};
   struct ReplacementFor_create_key{};
   struct ReplacementFor_create_wallet{};
   struct ReplacementFor_import_privkey{};
   struct ReplacementFor_unlock_wallet{};
   struct ReplacementFor_lock_wallet{};
};
}

namespace ReplacementFor_eosio {

struct ReplacementFor_async_result_visitor : public ReplacementFor_fc::ReplacementFor_visitor<std::string> {
   template<typename T>
   std::string operator()(const T& ReplacementFor_v) const {
      return ReplacementFor_fc::ReplacementFor_json::to_string(ReplacementFor_v);
   }
};

#define ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_call_name)\
   ReplacementFor_pixel_plugin::ReplacementFor_handle_exception(#ReplacementFor_call_name, ReplacementFor_fc::ReplacementFor_json::to_string(ReplacementFor_cmd), ReplacementFor_cb)

#define ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_call_name, ReplacementFor_call_result)\
[&ReplacementFor_cb, &ReplacementFor_cmd](const ReplacementFor_fc::ReplacementFor_static_variant<ReplacementFor_fc::exception_ptr, ReplacementFor_call_result>& result){\
   if (result.ReplacementFor_contains<ReplacementFor_fc::exception_ptr>()) {\
      try {\
         result.get<ReplacementFor_fc::exception_ptr>()->ReplacementFor_dynamic_rethrow_exception();\
      } catch (...) {\
         ReplacementFor_pixel_plugin::ReplacementFor_handle_exception(#ReplacementFor_call_name, ReplacementFor_fc::ReplacementFor_json::to_string(ReplacementFor_cmd), ReplacementFor_cb);\
      }\
   } else {\
      ReplacementFor_cb(result.ReplacementFor_visit(ReplacementFor_async_result_visitor()));\
   }\
}

using ReplacementFor_response_callback = std::function<void(const string&)>;

namespace ReplacementFor_cmd {
const string init = "init";
const string ReplacementFor_refresh = "refresh";
const string ReplacementFor_changedur = "changedur";
const string end = "end";
const string ReplacementFor_createacct = "createacct";
const string ReplacementFor_withdraw = "withdraw";
const string ReplacementFor_clearpixels = "clearpixels";
const string ReplacementFor_clearaccts = "clearaccts";
const string ReplacementFor_clearcanvs = "clearcanvs";
const string ReplacementFor_resetquota = "resetquota";
const string ReplacementFor_dump_tables = "dump_tables";
const string ReplacementFor_transfer = "transfer";
const string ReplacementFor_create_key = "create_key";
const string ReplacementFor_create_system_acct = "create_system_acct";
const string ReplacementFor_create_wallet = "create_wallet";
const string ReplacementFor_import_privkey = "import_privkey";
const string ReplacementFor_unlock_wallet = "unlock_wallet";
const string ReplacementFor_lock_wallet = "lock_wallet";
const string ReplacementFor_unknow = "unknow";

}

using namespace std;
struct ReplacementFor_message_handle {
   virtual ~ReplacementFor_message_handle() {}
   ReplacementFor_message_handle() {
      ReplacementFor_contract_name = ReplacementFor_pixel_plugin::ReplacementFor_contract_name;
   }

   virtual bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cb("{\"code\":\"500\",\"what\":\"unsupport type of message.\"}");
      throw ReplacementFor_fc::exception(ReplacementFor_unspecified_exception_code, "pixel exception", "unknow type of message.");
      return false;
   };
   static string ReplacementFor_contract_name;
   static string ReplacementFor_team_name;
};

string ReplacementFor_message_handle::ReplacementFor_contract_name = "eospixels";
string ReplacementFor_message_handle::ReplacementFor_team_name     = "magicsteam11";
template<typename T>
struct ReplacementFor_pixel_message_handle: public ReplacementFor_message_handle {};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::init>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello init." << endl;
      try{
         ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_contract_name}, ReplacementFor_contract_name, ReplacementFor_cmd::init, ReplacementFor_fc::ReplacementFor_variant{vector<string>{}},
               ReplacementFor_PIXEL_ASYNC_CALL(init, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel init message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(init);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_refresh>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello refresh." << endl;
     try{
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_team_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_refresh, ReplacementFor_fc::ReplacementFor_variant{vector<string>{}},
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_refresh, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel refresh message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_refresh);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_changedur>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello changedur." << endl;
     try{
        string ReplacementFor_duration =  ReplacementFor_cmd["duration"].ReplacementFor_as_string();

        ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{ReplacementFor_duration}};
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_team_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_changedur, ReplacementFor_action_args_var,
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_changedur, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel changedur message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_changedur);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::end>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello end." << endl;
     try{
        string ReplacementFor_account_name = ReplacementFor_cmd["account_name"].ReplacementFor_as_string();

        ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{ReplacementFor_account_name}};
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_account_name}, ReplacementFor_contract_name, ReplacementFor_cmd::end, ReplacementFor_action_args_var,
              ReplacementFor_PIXEL_ASYNC_CALL(end, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel end message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(end);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_createacct>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello createacct." << endl;
     try{
        string ReplacementFor_account_name = ReplacementFor_cmd["account_name"].ReplacementFor_as_string();

        ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{ReplacementFor_account_name}};
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_account_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_createacct, ReplacementFor_action_args_var,
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_createacct, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel createacct message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_createacct);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_withdraw>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello withdraw." << endl;
     try{
        string ReplacementFor_account_name = ReplacementFor_cmd["account_name"].ReplacementFor_as_string();

        ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{ReplacementFor_account_name}};
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_account_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_withdraw, ReplacementFor_action_args_var,
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_withdraw, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel withdraw message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_withdraw);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_clearpixels>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello clearpixels." << endl;
     try{
        string count = ReplacementFor_cmd["count"].ReplacementFor_as_string();
        string ReplacementFor_nonce = ReplacementFor_cmd["nonce"].ReplacementFor_as_string();

        ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{count, ReplacementFor_nonce}};
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_team_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_clearpixels, ReplacementFor_action_args_var,
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_clearpixels, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_clearpixels);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_clearaccts>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello clearaccts." << endl;
     try{
        string count = ReplacementFor_cmd["count"].ReplacementFor_as_string();
        string ReplacementFor_nonce = ReplacementFor_cmd["nonce"].ReplacementFor_as_string();

        ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{count, ReplacementFor_nonce}};
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_team_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_clearaccts, ReplacementFor_action_args_var,
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_clearaccts, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel clearaccts message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_clearaccts);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_clearcanvs>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello clearcanvs." << endl;
     try{
        string count = ReplacementFor_cmd["count"].ReplacementFor_as_string();
        string ReplacementFor_nonce = ReplacementFor_cmd["nonce"].ReplacementFor_as_string();

        ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{count, ReplacementFor_nonce}};
        ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_team_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_clearcanvs, ReplacementFor_action_args_var,
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_clearcanvs, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
     } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel clearcanvs message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_clearcanvs);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_resetquota>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello resetquota." << endl;
      try{
         ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_team_name}, ReplacementFor_contract_name, ReplacementFor_cmd::ReplacementFor_resetquota, ReplacementFor_fc::ReplacementFor_variant{vector<string>{}},
              ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_resetquota, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel resetquota message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_resetquota);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_dump_tables>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello dump_tables." << endl;
      try{
         auto ReplacementFor_ret = ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_get_table(ReplacementFor_cmd.ReplacementFor_as<ReplacementFor_chain_apis::ReplacementFor_read_only::ReplacementFor_get_table_rows_params>());
         ReplacementFor_cb(ReplacementFor_fc::ReplacementFor_json::to_string(ReplacementFor_ret));
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel dump_tables message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_dump_tables);
         return false;
      }
      return true;
   }

};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_transfer>: public ReplacementFor_message_handle {

   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello transfer." << endl;
      try{
         string ReplacementFor_from = ReplacementFor_cmd["from"].ReplacementFor_as_string();
         string ReplacementFor_to = ReplacementFor_cmd["to"].ReplacementFor_as_string();
         string ReplacementFor_quantity = ReplacementFor_cmd["quantity"].ReplacementFor_as_string();
         string ReplacementFor_referrer = ReplacementFor_cmd["referrer"].ReplacementFor_as_string();
         const auto& ReplacementFor_pixels = ReplacementFor_cmd["pixels"].ReplacementFor_get_array();

         string ReplacementFor_memo;
         for(const auto& ReplacementFor_pixel : ReplacementFor_pixels)
           ReplacementFor_memo.append(ReplacementFor_pixel.ReplacementFor_as_string()+",");

         if(!ReplacementFor_pixels.empty()) ReplacementFor_memo.erase(ReplacementFor_memo.end()-1);
         if(!ReplacementFor_referrer.empty()) ReplacementFor_memo.append(string(";") + ReplacementFor_referrer);

         ReplacementFor_fc::ReplacementFor_variant ReplacementFor_action_args_var{vector<string>{ReplacementFor_from, ReplacementFor_to, ReplacementFor_quantity, ReplacementFor_memo}};
         ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_push_action({ReplacementFor_from}, "eosio.token", ReplacementFor_cmd::ReplacementFor_transfer, ReplacementFor_action_args_var,
               ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_transfer, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_transfer);
         return false;
      }
      return true;
   }
};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_create_key>: public ReplacementFor_message_handle {
   using ReplacementFor_public_key_type = ReplacementFor_fc::ReplacementFor_crypto::ReplacementFor_public_key;
   using ReplacementFor_private_key_type = ReplacementFor_fc::ReplacementFor_crypto::ReplacementFor_private_key;
   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello create_key." << endl;
      try{
            auto ReplacementFor_pk    = ReplacementFor_private_key_type::generate();
            auto ReplacementFor_privs = string(ReplacementFor_pk);
            auto ReplacementFor_pubs  = string(ReplacementFor_pk.ReplacementFor_get_public_key());
            string ReplacementFor_resp_key = string("{\"code\":\"0\",\"type\":\"create_key\",\"Public_key\":\"") + ReplacementFor_pubs + string("\",") + string("\"Private_key\":\"") + ReplacementFor_privs + string("\"}");
            std::ReplacementFor_cout << ReplacementFor_resp_key <<std::endl;
            ReplacementFor_cb(ReplacementFor_resp_key);
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_create_key);
         return false;
      }
      return true;
   }
};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_create_system_acct>: public ReplacementFor_message_handle {
   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello create_system_acct." << endl;
      try{
         string ReplacementFor_creator = ReplacementFor_cmd["creator"].ReplacementFor_as_string();
         string ReplacementFor_permission = ReplacementFor_cmd["permission"].ReplacementFor_as_string();
         if (! ReplacementFor_permission.empty())
         {
            ReplacementFor_creator = ReplacementFor_permission;
         }

         ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_create_account({ReplacementFor_creator}, ReplacementFor_fc::ReplacementFor_variant(ReplacementFor_cmd),
               ReplacementFor_PIXEL_ASYNC_CALL(ReplacementFor_create_system_acct, ReplacementFor_chain_apis::ReplacementFor_read_write::ReplacementFor_push_transaction_results));
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_create_system_acct);
         return false;
      }
      return true;
   }
};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_create_wallet>: public ReplacementFor_message_handle {
   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello create_wallet." << endl;
      try{
         string name = ReplacementFor_cmd["wallet_name"].ReplacementFor_as_string();
         const auto& ReplacementFor_v = ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_create_wallet(name);
         string ReplacementFor_priv_key = ReplacementFor_v.ReplacementFor_get_string();
         string ReplacementFor_ret = string("{\"type\":\"create_wallet\",\"wallet_name\":\"") + name + string("\",") + string("\"Wallet_key\":\"") + ReplacementFor_priv_key + string("\"}");
         ReplacementFor_cb(ReplacementFor_ret);
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_create_wallet);
         return false;
      }
      return true;
   }
};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_import_privkey>: public ReplacementFor_message_handle {
   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello import_privkey." << endl;
      try{
         string name = ReplacementFor_cmd["wallet_name"].ReplacementFor_as_string();
         string ReplacementFor_wallet_key_str = ReplacementFor_cmd["priv_key"].ReplacementFor_as_string();
         ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_import_privkey(name,ReplacementFor_wallet_key_str);
         string ReplacementFor_resp_key = string("{\"code\":\"0\",\"type\":\"import_privkey\",\"wallet_name\":\"") + name + string("\",") + string("\"memoInfo\":\"") + string("import success") + string("\"}");
         ReplacementFor_cb(ReplacementFor_resp_key);
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_import_privkey);
         return false;
      }
      return true;
   }
};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_unlock_wallet>: public ReplacementFor_message_handle {
   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello unlock_wallet." << endl;
      try{
         string name = ReplacementFor_cmd["wallet_name"].ReplacementFor_as_string();
         string ReplacementFor_wallet_key_str = ReplacementFor_cmd["priv_key"].ReplacementFor_as_string();
         ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_unlock_wallet(name,ReplacementFor_wallet_key_str);
         string ReplacementFor_resp_key = string("{\"code\":\"0\",\"type\":\"unlock_wallet\",\"wallet_name\":\"") + name + string("\",") + string("\"memoInfo\":\"") + string("unlock success") + string("\"}");
         ReplacementFor_cb(ReplacementFor_resp_key);
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_unlock_wallet);
         return false;
      }
      return true;
   }
};

template<>
struct ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_lock_wallet>: public ReplacementFor_message_handle {
   bool ReplacementFor_handle_message(ReplacementFor_fc::ReplacementFor_variant& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb) {
      ReplacementFor_cout << "hello lock_wallet." << endl;
      try{
         string name = ReplacementFor_cmd["wallet_name"].ReplacementFor_as_string();
         ReplacementFor_plugin_lib::ReplacementFor_instance().ReplacementFor_lock_wallet(name);
         string ReplacementFor_resp_key = string("{\"code\":\"0\",\"type\":\"lock_wallet\",\"wallet_name\":\"") + name + string("\",") + string("\"memoInfo\":\"") + string("lock success") + string("\"}");
         ReplacementFor_cb(ReplacementFor_resp_key);
      } catch(  const ReplacementFor_fc::exception& ReplacementFor_e ) {
         ReplacementFor_elog( "pixel message error!!!");
         ReplacementFor_PIXEL_SYNC_CALL(ReplacementFor_lock_wallet);
         return false;
      }
      return true;
   }
};

ReplacementFor_message_handle* ReplacementFor_get_pixel_message_handle(const string&& s) {
   static map<string, ReplacementFor_message_handle*> ReplacementFor_handle = {
      {ReplacementFor_cmd::init, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::init>()},
      {ReplacementFor_cmd::ReplacementFor_refresh, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_refresh>()},
      {ReplacementFor_cmd::ReplacementFor_changedur, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_changedur>()},
      {ReplacementFor_cmd::end, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::end>()},
      {ReplacementFor_cmd::ReplacementFor_createacct, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_createacct>()},
      {ReplacementFor_cmd::ReplacementFor_withdraw, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_withdraw>()},
      {ReplacementFor_cmd::ReplacementFor_clearpixels, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_clearpixels>()},
      {ReplacementFor_cmd::ReplacementFor_clearaccts, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_clearaccts>()},
      {ReplacementFor_cmd::ReplacementFor_clearcanvs, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_clearcanvs>()},
      {ReplacementFor_cmd::ReplacementFor_resetquota, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_resetquota>()},
      {ReplacementFor_cmd::ReplacementFor_dump_tables, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_dump_tables>()},
      {ReplacementFor_cmd::ReplacementFor_transfer, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_transfer>()},
      {ReplacementFor_cmd::ReplacementFor_create_key, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_create_key>()},
      {ReplacementFor_cmd::ReplacementFor_create_system_acct, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_create_system_acct>()},
      {ReplacementFor_cmd::ReplacementFor_create_wallet, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_create_wallet>()},
      {ReplacementFor_cmd::ReplacementFor_import_privkey, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_import_privkey>()},
      {ReplacementFor_cmd::ReplacementFor_unlock_wallet, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_unlock_wallet>()},
      {ReplacementFor_cmd::ReplacementFor_lock_wallet, new ReplacementFor_pixel_message_handle<ReplacementFor_pixel_message_t::ReplacementFor_lock_wallet>()},
      {ReplacementFor_cmd::ReplacementFor_unknow, new ReplacementFor_message_handle()}
   };

   return ReplacementFor_handle.find(s) != ReplacementFor_handle.end() ? ReplacementFor_handle.at(s): ReplacementFor_handle.at(ReplacementFor_cmd::ReplacementFor_unknow);
}

} 

