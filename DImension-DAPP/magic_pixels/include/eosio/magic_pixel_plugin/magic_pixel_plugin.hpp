/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <appbase/application.hpp>
#include <eosio/chain_plugin/chain_plugin.hpp>

namespace eosio {
   using namespace appbase;

   class pixel_plugin : public appbase::plugin<pixel_plugin>
   {
      public:
        pixel_plugin();
        virtual ~pixel_plugin();

        APPBASE_PLUGIN_REQUIRES((chain_plugin))
        virtual void set_program_options(options_description& cli, options_description& cfg) override;

        void plugin_initialize(const variables_map& options);
        void plugin_startup();
        void plugin_shutdown();

        static void handle_exception(const char *call_name, const string& cmd, std::function<void(const std::string&)> cb);

      public:
        static string contract_name;
        static string team_name;

      private:
        std::unique_ptr<class pixel_plugin_impl> my;
   };

   string pixel_plugin::contract_name = "eospixels";
   string pixel_plugin::team_name     = "magicsteam11";

}
