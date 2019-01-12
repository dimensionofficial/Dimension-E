
#include "include/eosio/pixel_plugin/pixel_plugin.hpp"
#include "include/eosio/pixel_plugin/protocol.hpp"

#include <eosio/chain/types.hpp>

#include <eosio/chain/controller.hpp>
#include <eosio/chain/exceptions.hpp>
#include <eosio/chain/block.hpp>
#include <eosio/chain/plugin_interface.hpp>
#include <eosio/producer_plugin/producer_plugin.hpp>
#include <eosio/utilities/key_conversion.hpp>
#include <eosio/chain/contract_types.hpp>
#include <eosio/http_plugin/http_plugin.hpp>

#include <fc/network/message_buffer.hpp>
#include <fc/network/ip.hpp>
#include <fc/io/json.hpp>
#include <fc/io/raw.hpp>
#include <fc/log/appender.hpp>
#include <fc/container/flat.hpp>
#include <fc/reflect/variant.hpp>
#include <fc/crypto/rand.hpp>
#include <fc/exception/exception.hpp>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/host_name.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace ReplacementFor_eosio::ReplacementFor_chain::ReplacementFor_plugin_interface::ReplacementFor_compat;

namespace ReplacementFor_fc {
   extern std::ReplacementFor_unordered_map<std::ReplacementFor_string,ReplacementFor_logger>& ReplacementFor_get_logger_map();
}

namespace ReplacementFor_eosio {
   static ReplacementFor_appbase::ReplacementFor_abstract_plugin& ReplacementFor__pixel_plugin = ReplacementFor_app().ReplacementFor_register_plugin<ReplacementFor_pixel_plugin>();

   using std::ReplacementFor_vector;
   using std::ReplacementFor_deque;
   using std::ReplacementFor_shared_ptr;

   using ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_ip::ReplacementFor_tcp;
   using ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_ip::ReplacementFor_address_v4;
   using ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_ip::ReplacementFor_host_name;
   using ReplacementFor_boost::ReplacementFor_intrusive::ReplacementFor_rbtree;
   using ReplacementFor_boost::ReplacementFor_multi_index_container;

   using ReplacementFor_fc::ReplacementFor_time_point;
   using ReplacementFor_fc::ReplacementFor_time_point_sec;
   using ReplacementFor_chain::ReplacementFor_block_state_ptr;


   class ReplacementFor_psession;

   using ReplacementFor_psession_ptr = std::ReplacementFor_shared_ptr<ReplacementFor_psession>;
   using ReplacementFor_psession_wptr = std::ReplacementFor_weak_ptr<ReplacementFor_psession>;
   using ReplacementFor_response_func = std::ReplacementFor_function<void(int,ReplacementFor_string)>;
   using ReplacementFor_socket_ptr = ReplacementFor_shared_ptr<ReplacementFor_tcp::ReplacementFor_socket>;

   class ReplacementFor_pixel_plugin_impl {
   public:
      ReplacementFor_unique_ptr<ReplacementFor_tcp::ReplacementFor_acceptor>        ReplacementFor_acceptor;
      ReplacementFor_tcp::ReplacementFor_endpoint                    ReplacementFor_listen_endpoint;
      uint32_t                         ReplacementFor_num_clients = 0;

      std::ReplacementFor_map<ReplacementFor_chain::ReplacementFor_public_key_type,
               ReplacementFor_chain::ReplacementFor_private_key_type> ReplacementFor_private_keys; 


      ReplacementFor_psession_ptr ReplacementFor_find_connection( ReplacementFor_string ReplacementFor_host )const;

      std::ReplacementFor_set< ReplacementFor_psession_ptr >       ReplacementFor_connections;
      bool                             ReplacementFor_done = false;

      ReplacementFor_unique_ptr<ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_steady_timer> ReplacementFor_transaction_check;
      ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_steady_timer::ReplacementFor_duration   ReplacementFor_resp_expected_period;

      ReplacementFor_chain_plugin*                 ReplacementFor_chain_plug = nullptr;
      int                           ReplacementFor_started_sessions = 0;
      ReplacementFor_shared_ptr<ReplacementFor_tcp::ReplacementFor_resolver>     ReplacementFor_resolver;

      bool ReplacementFor_start_session( ReplacementFor_psession_ptr ReplacementFor_c );
      void ReplacementFor_start_listen_loop( );
      void ReplacementFor_start_read_message( ReplacementFor_psession_ptr ReplacementFor_c);

      void   ReplacementFor_close( ReplacementFor_psession_ptr ReplacementFor_c );


      void ReplacementFor_accepted_block_header(const ReplacementFor_block_state_ptr&);
      void ReplacementFor_accepted_block(const ReplacementFor_block_state_ptr&);
      void ReplacementFor_irreversible_block(const ReplacementFor_block_state_ptr&);
      void ReplacementFor_accepted_transaction(const ReplacementFor_transaction_metadata_ptr&);
      void ReplacementFor_applied_transaction(const ReplacementFor_transaction_trace_ptr&);
      void ReplacementFor_accepted_confirmation(const ReplacementFor_header_confirmation&);

      bool ReplacementFor_is_valid( const ReplacementFor_handshake_message &ReplacementFor_msg);

      void ReplacementFor_handle_message( ReplacementFor_psession_ptr ReplacementFor_c, const ReplacementFor_handshake_message &ReplacementFor_msg);

      void ReplacementFor_is_transaction_success(ReplacementFor_psession_ptr ReplacementFor_c);

      struct ReplacementFor_transcation_info {
         uint64_t ReplacementFor_count;
         uint32_t ReplacementFor_block_num;
         ReplacementFor_string ReplacementFor_id;
         ReplacementFor_string ReplacementFor_type;
         ReplacementFor_psession_wptr ReplacementFor_s;
         bool operator<(const ReplacementFor_transcation_info &ReplacementFor_other) const {
            return ReplacementFor_block_num < ReplacementFor_other.ReplacementFor_block_num;
         }
      };
      std::ReplacementFor_multiset<ReplacementFor_transcation_info> ReplacementFor_transcation_infos;

      std::ReplacementFor_multiset<ReplacementFor_transcation_info>& ReplacementFor_get_transcation_infos() { return ReplacementFor_transcation_infos; }
      ReplacementFor_boost::ReplacementFor_optional<std::ReplacementFor_pair<uint32_t, ReplacementFor_string>> ReplacementFor_transction_info_form_msg(const ReplacementFor_string& ReplacementFor_msg);
   };

   const ReplacementFor_fc::ReplacementFor_string ReplacementFor_logger_name("pixel_plugin_impl");
   ReplacementFor_fc::ReplacementFor_logger ReplacementFor_plogger;
   std::ReplacementFor_string ReplacementFor_plog_format;

#define ReplacementFor_peer_dlog( ReplacementFor_PEER, FORMAT, ... ) \
  ReplacementFor_FC_MULTILINE_MACRO_BEGIN \
   if( ReplacementFor_plogger.ReplacementFor_is_enabled( ReplacementFor_fc::ReplacementFor_log_level::ReplacementFor_debug ) ) \
      ReplacementFor_plogger.ReplacementFor_log( ReplacementFor_FC_LOG_MESSAGE( ReplacementFor_debug, ReplacementFor_plog_format + FORMAT, ReplacementFor___VA_ARGS__ (ReplacementFor_PEER->ReplacementFor_get_logger_variant()) ) ); \
  ReplacementFor_FC_MULTILINE_MACRO_END

#define ReplacementFor_peer_ilog( ReplacementFor_PEER, FORMAT, ... ) \
  ReplacementFor_FC_MULTILINE_MACRO_BEGIN \
   if( ReplacementFor_plogger.ReplacementFor_is_enabled( ReplacementFor_fc::ReplacementFor_log_level::ReplacementFor_info ) ) \
      ReplacementFor_plogger.ReplacementFor_log( ReplacementFor_FC_LOG_MESSAGE( ReplacementFor_info, ReplacementFor_plog_format + FORMAT, ReplacementFor___VA_ARGS__ (ReplacementFor_PEER->ReplacementFor_get_logger_variant()) ) ); \
  ReplacementFor_FC_MULTILINE_MACRO_END

#define ReplacementFor_peer_wlog( ReplacementFor_PEER, FORMAT, ... ) \
  ReplacementFor_FC_MULTILINE_MACRO_BEGIN \
   if( ReplacementFor_plogger.ReplacementFor_is_enabled( ReplacementFor_fc::ReplacementFor_log_level::ReplacementFor_warn ) ) \
      ReplacementFor_plogger.ReplacementFor_log( ReplacementFor_FC_LOG_MESSAGE( ReplacementFor_warn, ReplacementFor_plog_format + FORMAT, ReplacementFor___VA_ARGS__ (ReplacementFor_PEER->ReplacementFor_get_logger_variant()) ) ); \
  ReplacementFor_FC_MULTILINE_MACRO_END

#define ReplacementFor_peer_elog( ReplacementFor_PEER, FORMAT, ... ) \
  ReplacementFor_FC_MULTILINE_MACRO_BEGIN \
   if( ReplacementFor_plogger.ReplacementFor_is_enabled( ReplacementFor_fc::ReplacementFor_log_level::error ) ) \
      ReplacementFor_plogger.ReplacementFor_log( ReplacementFor_FC_LOG_MESSAGE( error, ReplacementFor_plog_format + FORMAT, ReplacementFor___VA_ARGS__ (ReplacementFor_PEER->ReplacementFor_get_logger_variant())) );   ReplacementFor_FC_MULTILINE_MACRO_END

   static ReplacementFor_pixel_plugin_impl *ReplacementFor_my_impl;

   


   constexpr auto     ReplacementFor_def_send_buffer_size_mb = 4;
   constexpr auto     ReplacementFor_def_send_buffer_size = 1024*1024*ReplacementFor_def_send_buffer_size_mb;
   constexpr auto     ReplacementFor_def_max_clients = 25; 
   constexpr auto     ReplacementFor_def_max_nodes_per_host = 1;
   constexpr auto     ReplacementFor_def_conn_retry_wait = 30;
   constexpr auto     ReplacementFor_def_txn_expire_wait = std::ReplacementFor_chrono::ReplacementFor_seconds(3);
   constexpr auto     ReplacementFor_def_resp_expected_wait = std::ReplacementFor_chrono::ReplacementFor_seconds(5);
   constexpr auto     ReplacementFor_def_sync_fetch_span = 100;
   constexpr uint32_t  ReplacementFor_def_max_just_send = 1500; 
   constexpr bool     ReplacementFor_large_msg_notify = false;

   constexpr auto     ReplacementFor_message_length_size = 4;
   constexpr auto     ReplacementFor_message_counter_size = 8;
   constexpr auto     ReplacementFor_message_header_size = ReplacementFor_message_length_size + ReplacementFor_message_counter_size;

   class ReplacementFor_psession : public std::ReplacementFor_enable_shared_from_this<ReplacementFor_psession> {
   public:
      explicit ReplacementFor_psession( ReplacementFor_string ReplacementFor_endpoint );

      explicit ReplacementFor_psession( ReplacementFor_socket_ptr ReplacementFor_s );
      ~ReplacementFor_psession();
      void ReplacementFor_initialize();

      ReplacementFor_socket_ptr              ReplacementFor_socket;

      ReplacementFor_fc::ReplacementFor_message_buffer<1024*1024>    ReplacementFor_pending_message_buffer;
      ReplacementFor_fc::ReplacementFor_optional<std::ReplacementFor_size_t>        ReplacementFor_outstanding_read_bytes;
      ReplacementFor_vector<char>                     ReplacementFor_rcv_buffer;

      ReplacementFor_string                  ReplacementFor_peer_addr;
      ReplacementFor_unique_ptr<ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_steady_timer> ReplacementFor_response_expected;

       

      const ReplacementFor_string ReplacementFor_peer_name() {return ReplacementFor_peer_addr;}
      bool ReplacementFor_connected();
      void ReplacementFor_close();



        void ReplacementFor_flush_queues();









      








      bool ReplacementFor_process_next_message(ReplacementFor_pixel_plugin_impl& ReplacementFor_impl, uint64_t ReplacementFor_count, uint32_t ReplacementFor_message_length);
      bool ReplacementFor_send_response(uint64_t ReplacementFor_count, const ReplacementFor_string& ReplacementFor_msg);

      ReplacementFor_fc::ReplacementFor_optional<ReplacementFor_fc::ReplacementFor_variant_object> ReplacementFor__logger_variant;
      const ReplacementFor_fc::ReplacementFor_variant_object& ReplacementFor_get_logger_variant()  {
         if (!ReplacementFor__logger_variant) {
            ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code ReplacementFor_ec;
            auto ReplacementFor_rep = ReplacementFor_socket->ReplacementFor_remote_endpoint(ReplacementFor_ec);
            ReplacementFor_string ReplacementFor_ip = ReplacementFor_ec ? "<unknown>" : ReplacementFor_rep.ReplacementFor_address().ReplacementFor_to_string();
            ReplacementFor_string ReplacementFor_port = ReplacementFor_ec ? "<unknown>" : std::ReplacementFor_to_string(ReplacementFor_rep.ReplacementFor_port());

            auto ReplacementFor_lep = ReplacementFor_socket->ReplacementFor_local_endpoint(ReplacementFor_ec);
            ReplacementFor_string ReplacementFor_lip = ReplacementFor_ec ? "<unknown>" : ReplacementFor_lep.ReplacementFor_address().ReplacementFor_to_string();
            ReplacementFor_string ReplacementFor_lport = ReplacementFor_ec ? "<unknown>" : std::ReplacementFor_to_string(ReplacementFor_lep.ReplacementFor_port());

            ReplacementFor__logger_variant.ReplacementFor_emplace(ReplacementFor_fc::ReplacementFor_mutable_variant_object()
               ("_name", ReplacementFor_peer_name())
               ("_ip", ReplacementFor_ip)
               ("_port", ReplacementFor_port)
               ("_lip", ReplacementFor_lip)
               ("_lport", ReplacementFor_lport)
            );
         }
         return *ReplacementFor__logger_variant;
      }
   };

   

   ReplacementFor_psession::ReplacementFor_psession( ReplacementFor_string ReplacementFor_endpoint )
      : ReplacementFor_socket( std::ReplacementFor_make_shared<ReplacementFor_tcp::ReplacementFor_socket>( std::ReplacementFor_ref( ReplacementFor_app().ReplacementFor_get_io_service() ))),
        ReplacementFor_peer_addr(ReplacementFor_endpoint),
        ReplacementFor_response_expected()
   {
      ReplacementFor_wlog( "created connection to ${n}", ("n", ReplacementFor_endpoint) );
      ReplacementFor_initialize();
   }

   ReplacementFor_psession::ReplacementFor_psession( ReplacementFor_socket_ptr ReplacementFor_s )
      : ReplacementFor_socket( ReplacementFor_s ),
        ReplacementFor_peer_addr(),
        ReplacementFor_response_expected()
   {
      ReplacementFor_wlog( "accepted network connection" );
      ReplacementFor_initialize();
   }

   ReplacementFor_psession::~ReplacementFor_psession() {}

   void ReplacementFor_psession::ReplacementFor_initialize() {
      ReplacementFor_response_expected.ReplacementFor_reset(new ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_steady_timer(ReplacementFor_app().ReplacementFor_get_io_service()));
   }

   bool ReplacementFor_psession::ReplacementFor_connected() {
      return (ReplacementFor_socket && ReplacementFor_socket->ReplacementFor_is_open());
   }

   void ReplacementFor_psession::ReplacementFor_close() {
      if(ReplacementFor_socket) {
         ReplacementFor_socket->ReplacementFor_close();
      }
      else {
         ReplacementFor_wlog("no socket to close!");
      }
      ReplacementFor_pending_message_buffer.ReplacementFor_reset();
   }

   bool ReplacementFor_psession::ReplacementFor_process_next_message(ReplacementFor_pixel_plugin_impl& ReplacementFor_impl, uint64_t ReplacementFor_count, uint32_t ReplacementFor_message_length) {
      try {
         auto ReplacementFor_index = ReplacementFor_pending_message_buffer.ReplacementFor_read_index();
         ReplacementFor_rcv_buffer.ReplacementFor_resize(ReplacementFor_message_length);

         ReplacementFor_pending_message_buffer.ReplacementFor_peek(ReplacementFor_rcv_buffer.ReplacementFor_data(), ReplacementFor_message_length, ReplacementFor_index);
         ReplacementFor_pending_message_buffer.ReplacementFor_advance_read_ptr(ReplacementFor_message_length);

         ReplacementFor_string ReplacementFor_s(ReplacementFor_rcv_buffer.ReplacementFor_data(), ReplacementFor_rcv_buffer.ReplacementFor_size());
         std::ReplacementFor_cout << "rev_message_body = " << ReplacementFor_s << std::ReplacementFor_endl;
         ReplacementFor_fc::ReplacementFor_variant ReplacementFor_cmd = ReplacementFor_fc::ReplacementFor_json::ReplacementFor_from_string(ReplacementFor_s);

          ReplacementFor_message_handle* ReplacementFor_handle = ReplacementFor_get_pixel_message_handle(ReplacementFor_cmd["type"].ReplacementFor_as_string());
         
         ReplacementFor_string ReplacementFor_type_string = ReplacementFor_cmd["type"].ReplacementFor_as_string();         

          ReplacementFor_psession_wptr ReplacementFor_session(ReplacementFor_shared_from_this());
          ReplacementFor_handle->ReplacementFor_handle_message(ReplacementFor_cmd, [ReplacementFor_count, ReplacementFor_session, ReplacementFor_type_string, this](const ReplacementFor_string& ReplacementFor_msg ) {
             try {
                auto ReplacementFor_s = ReplacementFor_session.ReplacementFor_lock();
                if(!ReplacementFor_s) throw ReplacementFor_fc::ReplacementFor_exception();
                auto ReplacementFor_info = ReplacementFor_my_impl->ReplacementFor_transction_info_form_msg(ReplacementFor_msg);
               
               if((ReplacementFor_type_string == ReplacementFor_string("transfer")) && ReplacementFor_info) 
                     
                     std::ReplacementFor_cout << "[ inserting: block_num  =" << ReplacementFor_info->ReplacementFor_first << "\t txs_id = "<< ReplacementFor_info->ReplacementFor_second << std::ReplacementFor_endl;

                if(ReplacementFor_info) {
                   ReplacementFor_my_impl->ReplacementFor_get_transcation_infos().ReplacementFor_insert(ReplacementFor_pixel_plugin_impl::ReplacementFor_transcation_info{ReplacementFor_count, ReplacementFor_info->ReplacementFor_first, ReplacementFor_info->ReplacementFor_second, ReplacementFor_type_string, ReplacementFor_s});

                   ReplacementFor_string ReplacementFor_ret = ReplacementFor_string("{\"code\":\"0\",\"cmd_type\":\"") + ReplacementFor_type_string + "\",\"transaction_id\":\"" + ReplacementFor_info->ReplacementFor_second + "\",\"confirmed\":\"waitting\"}";
                   ReplacementFor_s->ReplacementFor_send_response(ReplacementFor_count, ReplacementFor_ret);
                }else {
                   ReplacementFor_s->ReplacementFor_send_response(ReplacementFor_count, ReplacementFor_msg);
                }
             }
             catch(const std::ReplacementFor_exception &ReplacementFor_ex) {
                ReplacementFor_elog("Exception in pixel handle_message to ${s}", ("s",ReplacementFor_ex.ReplacementFor_what()));
                ReplacementFor_close();
             }
             catch(const ReplacementFor_fc::ReplacementFor_exception &ReplacementFor_ex) {
                ReplacementFor_elog("Exception in pixel handle_message to ${s}", ("s",ReplacementFor_ex.ReplacementFor_to_string()));
                ReplacementFor_close();
             }
             catch(...) {
                ReplacementFor_elog("Exception in pixel handle_message." );
                ReplacementFor_close();
             }
          });
      } catch(  const ReplacementFor_fc::ReplacementFor_exception& ReplacementFor_e ) {
         ReplacementFor_edump((ReplacementFor_e.ReplacementFor_to_detail_string() ));
         ReplacementFor_impl.ReplacementFor_close( ReplacementFor_shared_from_this() );
         return false;
      }
      return true;
   }

   bool ReplacementFor_psession::ReplacementFor_send_response(const uint64_t ReplacementFor_count, const ReplacementFor_string& ReplacementFor_msg) {
       if(ReplacementFor_msg.ReplacementFor_empty()) {
          ReplacementFor_elog("Send msg is empty." );
          return false;
       }

       int ReplacementFor_len = ReplacementFor_msg.ReplacementFor_size();
       ReplacementFor_shared_ptr<ReplacementFor_vector<char>> ReplacementFor_buf = ReplacementFor_make_shared<ReplacementFor_vector<char>>();
       ReplacementFor_buf->ReplacementFor_reserve(ReplacementFor_message_header_size+ReplacementFor_len);

       for( int ReplacementFor_i = 0; ReplacementFor_i < ReplacementFor_message_length_size; ++ReplacementFor_i) { ReplacementFor_buf->ReplacementFor_push_back(char(ReplacementFor_len >> (ReplacementFor_i*8) & 0xff)); }
       for( int ReplacementFor_i = 0; ReplacementFor_i < ReplacementFor_message_counter_size; ++ReplacementFor_i) { ReplacementFor_buf->ReplacementFor_push_back(char(ReplacementFor_count >> (ReplacementFor_i*8) & 0xff)); }
       for(auto& ReplacementFor_c : ReplacementFor_msg) ReplacementFor_buf->ReplacementFor_push_back(ReplacementFor_c);

       ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_async_write( *ReplacementFor_socket,
          ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_buffer( ReplacementFor_buf->ReplacementFor_data(), ReplacementFor_buf->ReplacementFor_size()),
          [ReplacementFor_buf](const ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code& ReplacementFor_ec, ReplacementFor_size_t ReplacementFor_bytes_transferred) {
             if(ReplacementFor_ec) {
                ReplacementFor_dlog("psession send error. the send len size: ${size}, ${error}, ${buf_size}",
                      ("size", ReplacementFor_bytes_transferred)("error",ReplacementFor_ec.ReplacementFor_message())("buf_size", ReplacementFor_buf->ReplacementFor_size()));
                return;
             }
          }
       );

      return true;
   }

   ReplacementFor_boost::ReplacementFor_optional<std::ReplacementFor_pair<uint32_t, ReplacementFor_string>> ReplacementFor_pixel_plugin_impl::ReplacementFor_transction_info_form_msg(const ReplacementFor_string& ReplacementFor_msg) {
      ReplacementFor_boost::ReplacementFor_optional<std::ReplacementFor_pair<uint32_t, ReplacementFor_string>> ReplacementFor_info;

      std::ReplacementFor_stringstream ReplacementFor_ss(ReplacementFor_msg);
      ReplacementFor_boost::ReplacementFor_property_tree::ReplacementFor_ptree ReplacementFor_root;
      ReplacementFor_boost::ReplacementFor_property_tree::ReplacementFor_ptree ReplacementFor_processed;
      ReplacementFor_boost::ReplacementFor_property_tree::ReplacementFor_read_json<ReplacementFor_boost::ReplacementFor_property_tree::ReplacementFor_ptree>(ReplacementFor_ss, ReplacementFor_root);

      if(ReplacementFor_root.ReplacementFor_find("transaction_id") != ReplacementFor_root.ReplacementFor_not_found() && ReplacementFor_root.ReplacementFor_find("processed") != ReplacementFor_root.ReplacementFor_not_found()) {
         ReplacementFor_string ReplacementFor_id = ReplacementFor_root.get<ReplacementFor_string>("transaction_id");

         ReplacementFor_processed = ReplacementFor_root.ReplacementFor_get_child("processed");
         if(ReplacementFor_processed.ReplacementFor_find("block_num") != ReplacementFor_processed.ReplacementFor_not_found()) {
            uint32_t ReplacementFor_block_num = ReplacementFor_processed.get<uint32_t>("block_num");
            ReplacementFor_info.ReplacementFor_emplace(std::ReplacementFor_make_pair(ReplacementFor_block_num, ReplacementFor_id));
         }
      }

      return ReplacementFor_info;
   }

   bool ReplacementFor_pixel_plugin_impl::ReplacementFor_start_session( ReplacementFor_psession_ptr ReplacementFor_con ) {
      ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_ip::ReplacementFor_tcp::ReplacementFor_no_delay ReplacementFor_nodelay( true );
      ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code ReplacementFor_ec;
      ReplacementFor_con->ReplacementFor_socket->ReplacementFor_set_option( ReplacementFor_nodelay, ReplacementFor_ec );
      if (ReplacementFor_ec) {
         ReplacementFor_elog( "connection failed to ${peer}: ${error}",
               ( "peer", ReplacementFor_con->ReplacementFor_peer_name())("error",ReplacementFor_ec.ReplacementFor_message()));
         ReplacementFor_close(ReplacementFor_con);
         return false;
      }
      else {
         ReplacementFor_start_read_message( ReplacementFor_con );
         ++ReplacementFor_started_sessions;
         return true;
      }
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_start_listen_loop( ) {
      auto ReplacementFor_socket = std::ReplacementFor_make_shared<ReplacementFor_tcp::ReplacementFor_socket>( std::ReplacementFor_ref( ReplacementFor_app().ReplacementFor_get_io_service() ) );
      ReplacementFor_acceptor->ReplacementFor_async_accept( *ReplacementFor_socket, [ReplacementFor_socket,this]( ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code ReplacementFor_ec ) {
            if( !ReplacementFor_ec ) {
               uint32_t ReplacementFor_visitors = 0;
               uint32_t ReplacementFor_from_addr = 0;
               auto ReplacementFor_paddr = ReplacementFor_socket->ReplacementFor_remote_endpoint(ReplacementFor_ec).ReplacementFor_address();
               if (ReplacementFor_ec) {
                  ReplacementFor_fc_elog(ReplacementFor_plogger,"Error getting remote endpoint: ${m}",("m", ReplacementFor_ec.ReplacementFor_message()));
               }
               else {
                  ++ReplacementFor_num_clients;
                  ReplacementFor_psession_ptr ReplacementFor_c = std::ReplacementFor_make_shared<ReplacementFor_psession>( ReplacementFor_socket );
                  ReplacementFor_connections.ReplacementFor_insert( ReplacementFor_c );
                  ReplacementFor_start_session( ReplacementFor_c );
               }
            } else {
               ReplacementFor_elog( "Error accepting connection: ${m}",( "m", ReplacementFor_ec.ReplacementFor_message() ) );
               
               switch (ReplacementFor_ec.ReplacementFor_value()) {
                  case ReplacementFor_ECONNABORTED:
                  case ReplacementFor_EMFILE:
                  case ReplacementFor_ENFILE:
                  case ReplacementFor_ENOBUFS:
                  case ReplacementFor_ENOMEM:
                  case ReplacementFor_EPROTO:
                     break;
                  default:
                     return;
               }
            }
            ReplacementFor_start_listen_loop();
         });
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_start_read_message( ReplacementFor_psession_ptr ReplacementFor_conn ) {

      try {
         if(!ReplacementFor_conn->ReplacementFor_socket) {
            return;
         }
         ReplacementFor_psession_wptr ReplacementFor_weak_conn = ReplacementFor_conn;

         std::ReplacementFor_size_t ReplacementFor_minimum_read = ReplacementFor_conn->ReplacementFor_outstanding_read_bytes ? *ReplacementFor_conn->ReplacementFor_outstanding_read_bytes : ReplacementFor_message_header_size;
         auto ReplacementFor_completion_handler = [ReplacementFor_minimum_read](ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code ReplacementFor_ec, std::ReplacementFor_size_t ReplacementFor_bytes_transferred) -> std::ReplacementFor_size_t {
            if (ReplacementFor_ec || ReplacementFor_bytes_transferred >= ReplacementFor_minimum_read ) {
               return 0;
            } else {
               return ReplacementFor_minimum_read - ReplacementFor_bytes_transferred;
            }
         };

         ReplacementFor_boost::ReplacementFor_asio::ReplacementFor_async_read(*ReplacementFor_conn->ReplacementFor_socket,
            ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_get_buffer_sequence_for_boost_async_read(), ReplacementFor_completion_handler,
            [this,ReplacementFor_weak_conn]( ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code ReplacementFor_ec, std::ReplacementFor_size_t ReplacementFor_bytes_transferred ) {
               auto ReplacementFor_conn = ReplacementFor_weak_conn.ReplacementFor_lock();
               if (!ReplacementFor_conn) {
                  return;
               }

               ReplacementFor_conn->ReplacementFor_outstanding_read_bytes.ReplacementFor_reset();

               try {
                  if( !ReplacementFor_ec ) {
                     if (ReplacementFor_bytes_transferred > ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_bytes_to_write()) {
                        ReplacementFor_elog("async_read_some callback: bytes_transfered = ${bt}, buffer.bytes_to_write = ${btw}",
                             ("bt",ReplacementFor_bytes_transferred)("btw",ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_bytes_to_write()));
                     }

                     ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_advance_write_ptr(ReplacementFor_bytes_transferred);
                     while (ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_bytes_to_read() > 0) {
                        uint32_t ReplacementFor_bytes_in_buffer = ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_bytes_to_read();

                        if (ReplacementFor_bytes_in_buffer < ReplacementFor_message_header_size) {
                           ReplacementFor_conn->ReplacementFor_outstanding_read_bytes.ReplacementFor_emplace(ReplacementFor_message_header_size - ReplacementFor_bytes_in_buffer);
                           break;
                        } else {
                           uint32_t ReplacementFor_message_length;
                           auto ReplacementFor_index = ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_read_index();
                           ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_peek(&ReplacementFor_message_length, sizeof(ReplacementFor_message_length), ReplacementFor_index);
                           if(ReplacementFor_message_length > ReplacementFor_def_send_buffer_size*2 || ReplacementFor_message_length == 0) {
                              ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code ReplacementFor_ec;
                              ReplacementFor_elog("incoming message length unexpected (${i}), from ${p}", ("i", ReplacementFor_message_length)("p",ReplacementFor_boost::ReplacementFor_lexical_cast<std::ReplacementFor_string>(ReplacementFor_conn->ReplacementFor_socket->ReplacementFor_remote_endpoint(ReplacementFor_ec))));
                              ReplacementFor_close(ReplacementFor_conn);
                              return;
                           }

                           auto ReplacementFor_total_message_bytes = ReplacementFor_message_length + ReplacementFor_message_header_size;

                           if (ReplacementFor_bytes_in_buffer >= ReplacementFor_total_message_bytes) {
                              ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_advance_read_ptr(ReplacementFor_message_length_size);

                              uint64_t ReplacementFor_count;
                              auto ReplacementFor_index = ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_read_index();
                              ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_peek(&ReplacementFor_count, sizeof(ReplacementFor_count), ReplacementFor_index);

                              ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_advance_read_ptr(ReplacementFor_message_counter_size);
                              if (!ReplacementFor_conn->ReplacementFor_process_next_message(*this, ReplacementFor_count, ReplacementFor_message_length)) {
                                 return;
                              }
                           } else {
                              auto ReplacementFor_outstanding_message_bytes = ReplacementFor_total_message_bytes - ReplacementFor_bytes_in_buffer;
                              auto ReplacementFor_available_buffer_bytes = ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_bytes_to_write();
                              if (ReplacementFor_outstanding_message_bytes > ReplacementFor_available_buffer_bytes) {
                                 ReplacementFor_conn->ReplacementFor_pending_message_buffer.ReplacementFor_add_space( ReplacementFor_outstanding_message_bytes - ReplacementFor_available_buffer_bytes );
                              }

                              ReplacementFor_conn->ReplacementFor_outstanding_read_bytes.ReplacementFor_emplace(ReplacementFor_outstanding_message_bytes);
                              break;
                           }
                        }
                     }
                     ReplacementFor_start_read_message(ReplacementFor_conn);
                  } else {
                     auto ReplacementFor_pname = ReplacementFor_conn->ReplacementFor_peer_name();
                     if (ReplacementFor_ec.ReplacementFor_value() != ReplacementFor_boost::ReplacementFor_asio::error::ReplacementFor_eof) {
                        ReplacementFor_elog( "Error reading message from ${p}: ${m}",("p",ReplacementFor_pname)( "m", ReplacementFor_ec.ReplacementFor_message() ) );
                     } else {
                        ReplacementFor_ilog( "Peer ${p} closed connection",("p",ReplacementFor_pname) );
                     }
                     ReplacementFor_close( ReplacementFor_conn );
                  }
               }
               catch(const std::ReplacementFor_exception &ReplacementFor_ex) {
                  ReplacementFor_string ReplacementFor_pname = ReplacementFor_conn ? ReplacementFor_conn->ReplacementFor_peer_name() : "no connection name";
                  ReplacementFor_elog("Exception in handling read data from ${p} ${s}",("p",ReplacementFor_pname)("s",ReplacementFor_ex.ReplacementFor_what()));
                  ReplacementFor_close( ReplacementFor_conn );
               }
               catch(const ReplacementFor_fc::ReplacementFor_exception &ReplacementFor_ex) {
                  ReplacementFor_string ReplacementFor_pname = ReplacementFor_conn ? ReplacementFor_conn->ReplacementFor_peer_name() : "no connection name";
                  ReplacementFor_elog("Exception in handling read data ${s}", ("p",ReplacementFor_pname)("s",ReplacementFor_ex.ReplacementFor_to_string()));
                  ReplacementFor_close( ReplacementFor_conn );
               }
               catch (...) {
                  ReplacementFor_string ReplacementFor_pname = ReplacementFor_conn ? ReplacementFor_conn->ReplacementFor_peer_name() : "no connection name";
                  ReplacementFor_elog( "Undefined exception hanlding the read data from connection ${p}",( "p",ReplacementFor_pname));
                  ReplacementFor_close( ReplacementFor_conn );
               }
            } );
      } catch (...) {
         ReplacementFor_string ReplacementFor_pname = ReplacementFor_conn ? ReplacementFor_conn->ReplacementFor_peer_name() : "no connection name";
         ReplacementFor_elog( "Undefined exception handling reading ${p}",("p",ReplacementFor_pname) );
         ReplacementFor_close( ReplacementFor_conn );
      }
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_is_transaction_success(ReplacementFor_psession_ptr ReplacementFor_c) {
      ReplacementFor_transaction_check->ReplacementFor_expires_from_now( ReplacementFor_resp_expected_period);
      ReplacementFor_transaction_check->ReplacementFor_async_wait( [this](ReplacementFor_boost::ReplacementFor_system::ReplacementFor_error_code ReplacementFor_ec) {
         if( !ReplacementFor_ec) {

         }
         else {
            ReplacementFor_elog( "Error connection: ${m}",( "m", ReplacementFor_ec.ReplacementFor_message()));
         }
      });
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_accepted_block_header(const ReplacementFor_block_state_ptr& ReplacementFor_block) {
      
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_accepted_block(const ReplacementFor_block_state_ptr& ReplacementFor_block) {
      uint32_t ReplacementFor_flag = 0;
      static uint32_t ReplacementFor_send_succeed_num = 0;
      static uint32_t ReplacementFor_send_fail_num = 0;
      static uint32_t ReplacementFor_transaction_num = 0;
      uint32_t ReplacementFor_irr_num = ReplacementFor_chain_plug->ReplacementFor_chain().ReplacementFor_last_irreversible_block_num();
      auto ReplacementFor_upper_bound = ReplacementFor_transcation_infos.ReplacementFor_upper_bound({0, ReplacementFor_block->ReplacementFor_block_num, "", "", ReplacementFor_psession_wptr()});
      for (auto ReplacementFor_elem : ReplacementFor_transcation_infos)
      {
         std::ReplacementFor_cout << "block num is " << ReplacementFor_elem.ReplacementFor_block_num << "\t type is " << ReplacementFor_elem.ReplacementFor_type << std::ReplacementFor_endl; 
      }
      for(auto ReplacementFor_it =  ReplacementFor_transcation_infos.ReplacementFor_begin(); ReplacementFor_it != ReplacementFor_upper_bound;) {
         
         std::ReplacementFor_cout << "The transcation_info size = " << ReplacementFor_transcation_infos.ReplacementFor_size() << std::ReplacementFor_endl;
         std::ReplacementFor_cout << "*it block id = " << ReplacementFor_it->ReplacementFor_block_num << "\tComing block_id =" << ReplacementFor_block->ReplacementFor_block_num << "\t irr_block_num = " << ReplacementFor_irr_num <<  std::ReplacementFor_endl;
         if(ReplacementFor_it->ReplacementFor_block_num <= ReplacementFor_irr_num) {
            std::ReplacementFor_cout << "1 -----------" << std::ReplacementFor_endl;
            const ReplacementFor_transcation_info& ReplacementFor_info = *ReplacementFor_it;
            auto ReplacementFor_conn = ReplacementFor_info.ReplacementFor_s.ReplacementFor_lock();
            if(ReplacementFor_conn) {
            std::ReplacementFor_cout << "2 -----------" << std::ReplacementFor_endl;
            ReplacementFor_signed_block_ptr ReplacementFor_sb = ReplacementFor_chain_plug->ReplacementFor_chain().ReplacementFor_fetch_block_by_number(ReplacementFor_info.ReplacementFor_block_num);
               if (ReplacementFor_sb){
                  std::ReplacementFor_cout << "3 -----------" << std::ReplacementFor_endl;
                  if( !ReplacementFor_sb->ReplacementFor_transactions.ReplacementFor_empty())
                  {
                     for(auto& ReplacementFor_transaction: ReplacementFor_sb->ReplacementFor_transactions) {
                           ReplacementFor_transaction_num ++;
                           std::ReplacementFor_cout << "[transaction_num ] = " << ReplacementFor_transaction_num << std::ReplacementFor_endl;
                           if((ReplacementFor_transaction.ReplacementFor_trx.ReplacementFor_contains<ReplacementFor_packed_transaction>() && ReplacementFor_info.ReplacementFor_id == ReplacementFor_transaction.ReplacementFor_trx.get<ReplacementFor_packed_transaction>().ReplacementFor_id().ReplacementFor_str())||
                              (ReplacementFor_transaction.ReplacementFor_trx.ReplacementFor_contains<ReplacementFor_transaction_id_type>() && ReplacementFor_info.ReplacementFor_id == ReplacementFor_transaction.ReplacementFor_trx.get<ReplacementFor_transaction_id_type>().ReplacementFor_str())) {
                           ReplacementFor_string ReplacementFor_ret = ReplacementFor_string("{\"code\":\"0\",\"cmd_type\":\"") + ReplacementFor_info.ReplacementFor_type + "\",\"transaction_id\":\"" + ReplacementFor_info.ReplacementFor_id + "\",\"confirmed\":\"successed\"}";

                           if(ReplacementFor_info.ReplacementFor_type == ReplacementFor_string("create_system_acct"))
                           {
                              ReplacementFor_ret = ReplacementFor_string("{\"code\":\"0\",\"cmd_type\":\"") + ReplacementFor_info.ReplacementFor_type + "\",\"transaction_id\":\"" + ReplacementFor_info.ReplacementFor_id + "\",\"account_confirmed\":\"successed\"}";
                           } 
                           ReplacementFor_conn->ReplacementFor_send_response(ReplacementFor_info.ReplacementFor_count, ReplacementFor_ret);
                           ReplacementFor_send_succeed_num ++;
                           ReplacementFor_flag ++;
                           
                           std::ReplacementFor_cout << "[send_succeed_num = ]" << ReplacementFor_send_succeed_num << std::ReplacementFor_endl;
                           std::ReplacementFor_cout << ReplacementFor_ret << std::ReplacementFor_endl;
                           
                        } else {
                              ReplacementFor_cout << "\n into fixed next block ---------------- 3 \n";
                              ReplacementFor_signed_block_ptr ReplacementFor_sb_next = ReplacementFor_chain_plug->ReplacementFor_chain().ReplacementFor_fetch_block_by_number(ReplacementFor_info.ReplacementFor_block_num + 1);
                              if(ReplacementFor_sb_next){
                                  for(auto& ReplacementFor_transaction_next: ReplacementFor_sb_next->ReplacementFor_transactions) {                          
                                    if((ReplacementFor_transaction_next.ReplacementFor_trx.ReplacementFor_contains<ReplacementFor_packed_transaction>() && ReplacementFor_info.ReplacementFor_id == ReplacementFor_transaction_next.ReplacementFor_trx.get<ReplacementFor_packed_transaction>().ReplacementFor_id().ReplacementFor_str())||
                                       (ReplacementFor_transaction_next.ReplacementFor_trx.ReplacementFor_contains<ReplacementFor_transaction_id_type>() && ReplacementFor_info.ReplacementFor_id == ReplacementFor_transaction_next.ReplacementFor_trx.get<ReplacementFor_transaction_id_type>().ReplacementFor_str())) {
                                       ReplacementFor_cout << "\n fixed next block succeed ---------------- 4 \n";
                                       ReplacementFor_string ReplacementFor_ret = ReplacementFor_string("{\"code\":\"0\",\"cmd_type\":\"") + ReplacementFor_info.ReplacementFor_type + "\",\"transaction_id\":\"" + ReplacementFor_info.ReplacementFor_id + "\",\"confirmed\":\"successed\"}";
                                       ReplacementFor_conn->ReplacementFor_send_response(ReplacementFor_info.ReplacementFor_count, ReplacementFor_ret);
                                       ReplacementFor_send_succeed_num ++;
                                       
                                       std::ReplacementFor_cout << "[send_succeed_num = ]" << ReplacementFor_send_succeed_num << std::ReplacementFor_endl;
                                       std::ReplacementFor_cout << ReplacementFor_ret << std::ReplacementFor_endl;
                                    }else{
                                          
                                          ReplacementFor_string ReplacementFor_ret = ReplacementFor_string("{\"code\":\"0\",\"cmd_type\":\"") + ReplacementFor_info.ReplacementFor_type + "\",\"transaction_id\":\"" + ReplacementFor_info.ReplacementFor_id + "\",\"confirmed\":\"failed\"}";
                                          ReplacementFor_conn->ReplacementFor_send_response(ReplacementFor_info.ReplacementFor_count, ReplacementFor_ret);
                                          ReplacementFor_send_fail_num ++;
                                          std::ReplacementFor_cout << "[send_fail_num = ]" << ReplacementFor_send_fail_num << std::ReplacementFor_endl;
                                          
                                          std::ReplacementFor_cout << ReplacementFor_ret << std::ReplacementFor_endl;
                                    }
                                 }
                              }   
                        }
                     } 
                  } else{
                     ReplacementFor_cout << "\n into fixed next block ---------------- 1 \n";
                     ReplacementFor_signed_block_ptr ReplacementFor_sb_next = ReplacementFor_chain_plug->ReplacementFor_chain().ReplacementFor_fetch_block_by_number(ReplacementFor_info.ReplacementFor_block_num + 1);
                     if(ReplacementFor_sb_next){
                        ReplacementFor_cout << "\n into fixed next block ---------------- 2 \n";
                        for(auto& ReplacementFor_transaction_next: ReplacementFor_sb_next->ReplacementFor_transactions) {                          
                           if((ReplacementFor_transaction_next.ReplacementFor_trx.ReplacementFor_contains<ReplacementFor_packed_transaction>() && ReplacementFor_info.ReplacementFor_id == ReplacementFor_transaction_next.ReplacementFor_trx.get<ReplacementFor_packed_transaction>().ReplacementFor_id().ReplacementFor_str())||
                              (ReplacementFor_transaction_next.ReplacementFor_trx.ReplacementFor_contains<ReplacementFor_transaction_id_type>() && ReplacementFor_info.ReplacementFor_id == ReplacementFor_transaction_next.ReplacementFor_trx.get<ReplacementFor_transaction_id_type>().ReplacementFor_str())) {
                              ReplacementFor_cout << "\n fixed next block succeed ---------------- \n";
                              ReplacementFor_string ReplacementFor_ret = ReplacementFor_string("{\"code\":\"0\",\"cmd_type\":\"") + ReplacementFor_info.ReplacementFor_type + "\",\"transaction_id\":\"" + ReplacementFor_info.ReplacementFor_id + "\",\"confirmed\":\"successed\"}";
                              ReplacementFor_conn->ReplacementFor_send_response(ReplacementFor_info.ReplacementFor_count, ReplacementFor_ret);
                              ReplacementFor_send_succeed_num ++;
                              
                              std::ReplacementFor_cout << "[send_succeed_num = ]" << ReplacementFor_send_succeed_num << std::ReplacementFor_endl;
                              std::ReplacementFor_cout << ReplacementFor_ret << std::ReplacementFor_endl;
                           } 
                        }
                     }   
                  } 
               } 
            }   

            ReplacementFor_it = ReplacementFor_transcation_infos.ReplacementFor_erase(ReplacementFor_it);
         } else {
               ++ReplacementFor_it;
         } 
      }
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_accepted_transaction(const ReplacementFor_transaction_metadata_ptr& ReplacementFor_md) {
      
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_applied_transaction(const ReplacementFor_transaction_trace_ptr& ReplacementFor_txn) {
      
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_accepted_confirmation(const ReplacementFor_header_confirmation& ReplacementFor_head) {
      
   }

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_irreversible_block(const ReplacementFor_block_state_ptr&ReplacementFor_block) {}

   void ReplacementFor_pixel_plugin_impl::ReplacementFor_close( ReplacementFor_psession_ptr ReplacementFor_c ) {
      if( ReplacementFor_c->ReplacementFor_peer_addr.ReplacementFor_empty( ) && ReplacementFor_c->ReplacementFor_socket->ReplacementFor_is_open() ) {
         if (ReplacementFor_num_clients == 0) {
            ReplacementFor_fc_wlog( ReplacementFor_plogger, "num_clients already at 0");
         }
         else {
            --ReplacementFor_num_clients;
         }
      }
      ReplacementFor_c->ReplacementFor_close();
   }

   void ReplacementFor_pixel_plugin::ReplacementFor_plugin_initialize( const ReplacementFor_variables_map& ReplacementFor_options ) {
      ReplacementFor_ilog("Initialize pixel plugin");
      try {
          if( ReplacementFor_options.ReplacementFor_count( "pixel-contract-name" ))
            ReplacementFor_contract_name = ReplacementFor_options.ReplacementFor_at( "pixel-contract-name" ).ReplacementFor_as<ReplacementFor_string>();

          ReplacementFor_my->ReplacementFor_resp_expected_period = ReplacementFor_def_resp_expected_wait;
          ReplacementFor_my->ReplacementFor_resolver = std::ReplacementFor_make_shared<ReplacementFor_tcp::ReplacementFor_resolver>( std::ReplacementFor_ref( ReplacementFor_app().ReplacementFor_get_io_service()));

          ReplacementFor_tcp::ReplacementFor_resolver::ReplacementFor_query ReplacementFor_query( ReplacementFor_tcp::ReplacementFor_v4(), "0.0.0.0", "9527");
          

         ReplacementFor_my->ReplacementFor_listen_endpoint = *ReplacementFor_my->ReplacementFor_resolver->ReplacementFor_resolve( ReplacementFor_query );

         ReplacementFor_my->ReplacementFor_acceptor.ReplacementFor_reset( new ReplacementFor_tcp::ReplacementFor_acceptor( ReplacementFor_app().ReplacementFor_get_io_service()));
         ReplacementFor_my->ReplacementFor_chain_plug = ReplacementFor_app().ReplacementFor_find_plugin<ReplacementFor_chain_plugin>();

      } ReplacementFor_FC_LOG_AND_RETHROW()
   }

   void ReplacementFor_pixel_plugin::ReplacementFor_plugin_startup() {
      if( ReplacementFor_my->ReplacementFor_acceptor ) {
         ReplacementFor_my->ReplacementFor_acceptor->ReplacementFor_open(ReplacementFor_my->ReplacementFor_listen_endpoint.ReplacementFor_protocol());
         ReplacementFor_my->ReplacementFor_acceptor->ReplacementFor_set_option(ReplacementFor_tcp::ReplacementFor_acceptor::ReplacementFor_reuse_address(true));
         try {
           ReplacementFor_my->ReplacementFor_acceptor->ReplacementFor_bind(ReplacementFor_my->ReplacementFor_listen_endpoint);
         } catch (const std::ReplacementFor_exception& ReplacementFor_e) {
           ReplacementFor_ilog("pixel_plugin::plugin_startup failed to bind to port ${port}",
             ("port", ReplacementFor_my->ReplacementFor_listen_endpoint.ReplacementFor_port()));
           throw ReplacementFor_e;
         }
         ReplacementFor_my->ReplacementFor_acceptor->ReplacementFor_listen();
         ReplacementFor_ilog("starting listener...");
         ReplacementFor_my->ReplacementFor_start_listen_loop();
      }
      ReplacementFor_chain::ReplacementFor_controller&ReplacementFor_cc = ReplacementFor_my->ReplacementFor_chain_plug->ReplacementFor_chain();
      {

             ReplacementFor_cc.ReplacementFor_accepted_block.ReplacementFor_connect(  ReplacementFor_boost::ReplacementFor_bind(&ReplacementFor_pixel_plugin_impl::ReplacementFor_accepted_block, ReplacementFor_my.get(), ReplacementFor__1));




      }
   }

   void ReplacementFor_pixel_plugin::ReplacementFor_plugin_shutdown() {
      try {
         ReplacementFor_ilog( "shutdown.." );
         ReplacementFor_my->ReplacementFor_done = true;
         if( ReplacementFor_my->ReplacementFor_acceptor ) {
            ReplacementFor_ilog( "close acceptor" );
            ReplacementFor_my->ReplacementFor_acceptor->ReplacementFor_close();

            ReplacementFor_ilog( "close ${s} connections",( "s",ReplacementFor_my->ReplacementFor_connections.ReplacementFor_size()) );
            auto ReplacementFor_cons = ReplacementFor_my->ReplacementFor_connections;
            for( auto ReplacementFor_con : ReplacementFor_cons ) {
               ReplacementFor_my->ReplacementFor_close( ReplacementFor_con);
            }

            ReplacementFor_my->ReplacementFor_acceptor.ReplacementFor_reset(nullptr);
         }
         ReplacementFor_ilog( "exit shutdown" );
      }
      ReplacementFor_FC_CAPTURE_AND_RETHROW()
   }

   void ReplacementFor_pixel_plugin::ReplacementFor_handle_exception(const char *ReplacementFor_call_name, const ReplacementFor_string& ReplacementFor_cmd, ReplacementFor_response_callback ReplacementFor_cb ) {
      static bool ReplacementFor_verbose_errors = false;
      try {
         try {
            throw;
         } catch (ReplacementFor_chain::ReplacementFor_unsatisfied_authorization& ReplacementFor_e) {
            ReplacementFor_error_results ReplacementFor_results{401, "UnAuthorized", ReplacementFor_error_results::ReplacementFor_error_info(ReplacementFor_e, ReplacementFor_verbose_errors)};
            ReplacementFor_cb( ReplacementFor_fc::ReplacementFor_json::ReplacementFor_to_string( ReplacementFor_results ));
         } catch (ReplacementFor_chain::ReplacementFor_tx_duplicate& ReplacementFor_e) {
            ReplacementFor_error_results ReplacementFor_results{409, "Conflict", ReplacementFor_error_results::ReplacementFor_error_info(ReplacementFor_e, ReplacementFor_verbose_errors)};
            ReplacementFor_cb(ReplacementFor_fc::ReplacementFor_json::ReplacementFor_to_string( ReplacementFor_results ));
         } catch (ReplacementFor_fc::ReplacementFor_eof_exception& ReplacementFor_e) {
            ReplacementFor_error_results ReplacementFor_results{422, "Unprocessable Entity", ReplacementFor_error_results::ReplacementFor_error_info(ReplacementFor_e, ReplacementFor_verbose_errors)};
            ReplacementFor_cb(ReplacementFor_fc::ReplacementFor_json::ReplacementFor_to_string( ReplacementFor_results ));
            ReplacementFor_dlog("Bad arguments: ${cmd}", ("cmd", ReplacementFor_cmd));
         } catch (ReplacementFor_fc::ReplacementFor_exception& ReplacementFor_e) {
            ReplacementFor_error_results ReplacementFor_results{500, "Internal Service Error", ReplacementFor_error_results::ReplacementFor_error_info(ReplacementFor_e, ReplacementFor_verbose_errors)};
            ReplacementFor_cb(ReplacementFor_fc::ReplacementFor_json::ReplacementFor_to_string( ReplacementFor_results ));
            if (ReplacementFor_e.ReplacementFor_code() != ReplacementFor_chain::ReplacementFor_greylist_net_usage_exceeded::ReplacementFor_code_value ) {
               ReplacementFor_elog( "FC Exception encountered while processing pixel.${call}", ( "call", ReplacementFor_call_name ));
               ReplacementFor_dlog( "Exception Details: ${e}", ("e", ReplacementFor_e.ReplacementFor_to_detail_string()));
            }
         } catch (std::ReplacementFor_exception& ReplacementFor_e) {
            ReplacementFor_error_results ReplacementFor_results{500, "Internal Service Error", ReplacementFor_error_results::ReplacementFor_error_info(ReplacementFor_fc::ReplacementFor_exception( ReplacementFor_FC_LOG_MESSAGE( error, ReplacementFor_e.ReplacementFor_what())), ReplacementFor_verbose_errors)};
            ReplacementFor_cb( ReplacementFor_fc::ReplacementFor_json::ReplacementFor_to_string( ReplacementFor_results ));
            ReplacementFor_elog( "STD Exception encountered while processing pixel.${call}", ( "call", ReplacementFor_call_name ));
            ReplacementFor_dlog( "Exception Details: ${e}", ("e", ReplacementFor_e.ReplacementFor_what()));
         } catch (...) {
            ReplacementFor_error_results ReplacementFor_results{500, "Internal Service Error",
               ReplacementFor_error_results::ReplacementFor_error_info(ReplacementFor_fc::ReplacementFor_exception( ReplacementFor_FC_LOG_MESSAGE( error, "Unknown Exception" )), ReplacementFor_verbose_errors)};
            ReplacementFor_cb(ReplacementFor_fc::ReplacementFor_json::ReplacementFor_to_string( ReplacementFor_results ));
            ReplacementFor_elog( "Unknown Exception encountered while processing ${call}", ( "call", ReplacementFor_call_name ));
         }
      } catch (...) {
         ReplacementFor_error_results ReplacementFor_results{500, "Internal Service Error", ReplacementFor_error_results::ReplacementFor_error_info(ReplacementFor_fc::ReplacementFor_exception( ReplacementFor_FC_LOG_MESSAGE( error, "unknow")), ReplacementFor_verbose_errors)};
         ReplacementFor_cb(ReplacementFor_fc::ReplacementFor_json::ReplacementFor_to_string( ReplacementFor_results ));
         std::ReplacementFor_cerr << "Exception attempting to handle exception for pixel." << ReplacementFor_call_name << std::ReplacementFor_endl;
      }
   }


   ReplacementFor_pixel_plugin::ReplacementFor_pixel_plugin():ReplacementFor_my( new ReplacementFor_pixel_plugin_impl ) { ReplacementFor_my_impl = ReplacementFor_my.get();}
   ReplacementFor_pixel_plugin::~ReplacementFor_pixel_plugin() {}

   void ReplacementFor_pixel_plugin::ReplacementFor_set_program_options( ReplacementFor_options_description&  , ReplacementFor_options_description& ReplacementFor_cfg )
   {
      ReplacementFor_cfg.ReplacementFor_add_options()( "pixel-contract-name", ReplacementFor_bpo::ReplacementFor_value<ReplacementFor_string>()->ReplacementFor_default_value( "eospixels" ), "The name of pixel contract.");
      ReplacementFor_cfg.ReplacementFor_add_options()( "pixel-team-name", ReplacementFor_bpo::ReplacementFor_value<ReplacementFor_string>()->ReplacementFor_default_value( "magicsteam11" ), "The name of pixel team.");
   }
}

