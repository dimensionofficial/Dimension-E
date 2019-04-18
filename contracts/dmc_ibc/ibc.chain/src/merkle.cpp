/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <ibc.chain/merkle.hpp>

namespace eosio {

   digest_type make_canonical_left(const digest_type& val) {
      digest_type canonical_l = val;
      canonical_l.hash[0] &= 0x7F;
      return canonical_l;
   }

   digest_type make_canonical_right(const digest_type& val) {
      digest_type canonical_r = val;
      canonical_r.hash[0] |= 0x80;
      return canonical_r;
   }

   bool is_canonical_left(const digest_type& val) {
      return (val.hash[0] & 0x80) == 0;
   }

   bool is_canonical_right(const digest_type& val) {
      return (val.hash[0] & 0x80) != 0;
   }

   digest_type merkle(std::vector<digest_type> ids) {
      if( 0 == ids.size() ) { return digest_type(); }

      while( ids.size() > 1 ) {
         if( ids.size() % 2 )
            ids.push_back(ids.back());

         for (int i = 0; i < ids.size() / 2; i++) {
            ids[i] = sha256hash(make_canonical_pair(ids[2 * i], ids[(2 * i) + 1]));
         }

         ids.resize(ids.size() / 2);
      }

      return ids.front();
   }

} // eosio
