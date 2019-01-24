



#include <eosio/chain/block.hpp>
#include <eosio/chain/merkle.hpp>
#include <fc/io/raw.hpp>
#include <fc/bitutil.hpp>
#include <algorithm>

namespace R { namespace R {
   R_D R_B::R()const
   {
      return R_D::hash(*this);
   }

   uint32_t R_B::R_N_F(const R_B_I& id)
   {
      return R::R_E_R(id.R__[0]);
   }

   R_B_I R_B::id()const
   {
      
      R_B_I R = R(); 
      R.R__[0] &= 0xffffffff00000000;
      R.R__[0] += R::R_E_R(R_B()); 
      return R;
   }


} }

