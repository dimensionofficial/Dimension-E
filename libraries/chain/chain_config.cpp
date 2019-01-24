




#include <eosio/chain/chain_config.hpp>
#include <eosio/chain/exceptions.hpp>

namespace R { namespace R {

   void R_C::R()const {
      R_E( R_T_B_N_U <= R::R_P, R_A_V,
                  "target block net usage percentage cannot exceed 100%" );
      R_E( R_T_B_N_U >= R::R_P/10, R_A_V,
                  "target block net usage percentage must be at least 0.1%" );
      R_E( R_T_B_C_U <= R::R_P, R_A_V,
                  "target block cpu usage percentage cannot exceed 100%" );
      R_E( R_T_B_C_U >= R::R_P/10, R_A_V,
                  "target block cpu usage percentage must be at least 0.1%" );

      R_E( R_M_T_N < R_M_B_N, R_A_V,
                  "max transaction net usage must be less than max block net usage" );
      R_E( R_M_T_C < R_M_B_C, R_A_V,
                  "max transaction cpu usage must be less than max block cpu usage" );

      R_E( R_B_P_T_N < R_M_T_N, R_A_V,
                  "base net usage per transaction must be less than the max transaction net usage" );
      R_E( (R_M_T_N - R_B_P_T_N) >= R::R_M_N_U_D_B_B_A_M_F,
                  R_A_V,
                  "max transaction net usage must be at least ${delta} bytes larger than base net usage per transaction",
                  ("delta", R::R_M_N_U_D_B_B_A_M_F) );
      R_E( R_C_F_D_N_U > 0, R_A_V,
                  "net usage discount ratio for context free data cannot have a 0 denominator" );
      R_E( R_C_F_D_N_U <= R_C_F_D_N_U, R_A_V,
                  "net usage discount ratio for context free data cannot exceed 1" );

      R_E( R_M_T_C <= R_M_T_C, R_A_V,
                  "min transaction cpu usage cannot exceed max transaction cpu usage" );
      R_E( R_M_T_C < (R_M_B_C - R_M_T_C), R_A_V,
                  "max transaction cpu usage must be at less than the difference between the max block cpu usage and the min transaction cpu usage" );

      R_E( 1 <= R_M_A, R_A_V,
                  "max authority depth should be at least 1" );
}

} } 

