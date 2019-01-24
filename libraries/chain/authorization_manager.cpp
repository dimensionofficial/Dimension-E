




#include <eosio/chain/authorization_manager.hpp>
#include <eosio/chain/exceptions.hpp>
#include <eosio/chain/permission_object.hpp>
#include <eosio/chain/permission_link_object.hpp>
#include <eosio/chain/authority_checker.hpp>
#include <eosio/chain/controller.hpp>
#include <eosio/chain/global_property_object.hpp>
#include <eosio/chain/contract_types.hpp>
#include <eosio/chain/generated_transaction_object.hpp>
#include <boost/tuple/tuple_io.hpp>

namespace R { namespace R {

   R_A::R_A(R& R, R& R)
   :R__(R),R__(R){}

   void R_A::R_A() {
      R__.R_A<R_P>();
      R__.R_A<R_P_U>();
      R__.R_A<R_P_L>();
   }

   void R_A::R_I() {
      R__.R<R_P>([](auto&){}); 
   }

   const R_P& R_A::R_C( R_A R,
                                                                      R_P name,
                                                                      R_P_I R,
                                                                      const R& R,
                                                                      R_T R_I_C
                                                                    )
   {
      auto R_C = R_I_C;
      if( R_C == R_T() ) {
         R_C = R__.R_P_B();
      }

      const auto& R_P = R__.R<R_P_U>([&](auto& p) {
         p.R_L = R_C;
      });

      const auto& R = R__.R<R_P>([&](auto& p) {
         p.R_U     = R_P.id;
         p.R       = R;
         p.R        = R;
         p.name         = name;
         p.R_L = R_C;
         p.R         = R;
      });
      return R;
   }

   const R_P& R_A::R_C( R_A R,
                                                                      R_P name,
                                                                      R_P_I R,
                                                                      R&& R,
                                                                      R_T R_I_C
                                                                    )
   {
      auto R_C = R_I_C;
      if( R_C == R_T() ) {
         R_C = R__.R_P_B();
      }

      const auto& R_P = R__.R<R_P_U>([&](auto& p) {
         p.R_L = R_C;
      });

      const auto& R = R__.R<R_P>([&](auto& p) {
         p.R_U     = R_P.id;
         p.R       = R;
         p.R        = R;
         p.name         = name;
         p.R_L = R_C;
         p.R         = std::move(R);
      });
      return R;
   }

   void R_A::R_M( const R_P& R, const R& R ) {
      R__.R( R, [&](R_P& R) {
         R.R = R;
         R.R_L = R__.R_P_B();
      });
   }

   void R_A::R_R( const R_P& R ) {
      const auto& index = R__.template R_G<R_P, R_B>();
      auto R = index.equal_range(R.id);
      R_E( R.first == R.second, R_A_V,
                  "Cannot remove a permission which has children. Remove the children first.");

      R__.R_G_M<R_P_U>().R_R( R.R_U.R__ );
      R__.remove( R );
   }

   void R_A::R_U_P( const R_P& R ) {
      const auto& R = R__.get<R_P_U, R_B>( R.R_U );
      R__.R( R, [&](R_P_U& p) {
         p.R_L = R__.R_P_B();
      });
   }

   R::R_T R_A::R_G_P_L( const R_P& R )const {
      return R__.get<R_P_U, R_B>( R.R_U ).R_L;
   }

   const R_P*  R_A::R_F( const R_P& R )const
   { try {
      R_E( !R.R.empty() && !R.R.empty(), R_I, "Invalid permission" );
      return R__.find<R_P, R_B>( R::make_tuple(R.R,R.R) );
   } R_E_R( R::R_P_Q, "Failed to retrieve permission: ${level}", ("level", R) ) }

   const R_P&  R_A::R_G( const R_P& R )const
   { try {
      R_E( !R.R.empty() && !R.R.empty(), R_I, "Invalid permission" );
      return R__.get<R_P, R_B>( R::make_tuple(R.R,R.R) );
   } R_E_R( R::R_P_Q, "Failed to retrieve permission: ${level}", ("level", R) ) }

   R<R_P> R_A::R_L_L( R_A R_A,
                                                                              R_A R,
                                                                              R_A R_A
                                                                            )const
   {
      try {
         
         auto R = R::make_tuple(R_A, R, R_A);
         auto R = R__.find<R_P_L, R_B_A>(R);
         
         if (R == nullptr) {
            R::get<2>(R) = "";
            R = R__.find<R_P_L, R_B_A>(R);
         }

         
         if (R != nullptr) {
            return R->R_R;
         }
         return R<R_P>();

       
      } R_F_C_A((R_A)(R)(R_A))
   }

   R<R_P> R_A::R_L_M( R_A R_A,
                                                                               R_A R,
                                                                               R_A R_A
                                                                             )const
   {
      
      if( R == R::R_S_A ) {
          R_E( R_A != R::R_G() &&
                     R_A != R::R_G() &&
                     R_A != R::R_G() &&
                     R_A != R::R_G() &&
                     R_A != R::R_G(),
                     R_U_M_P,
                     "cannot call lookup_minimum_permission on native actions that are not allowed to be linked to minimum permissions" );
      }

      try {
         R<R_P> R_L = R_L_L(R_A, R, R_A);
         if( !R_L )
            return R::R_A;

         if( *R_L == R::R_E_A )
            return R<R_P>();

         return R_L;
      } R_F_C_A((R_A)(R)(R_A))
   }

   void R_A::R_C_U( const R& R,
                                                               const vector<R_P>& R
                                                             )const
   {
      R_E( R.size() == 1, R_I_A,
                  "updateauth action should only have one declared authorization" );
      const auto& R = R[0];
      R_E( R.R == R.R, R_I_A,
                  "the owner of the affected permission needs to be the actor of the declared authorization" );

      const auto* R_M = R_F({R.R, R.R});
      if( !R_M ) { 
         R_M = &R_G({R.R, R.R});
      }

      R_E( R_G(R).R( *R_M,
                                                  R__.R_G<R_P>().R() ),
                  R_I_A,
                  "updateauth action declares irrelevant authority '${auth}'; minimum authority is ${min}",
                  ("R", R)("min", R_P{R.R, R_M->name}) );
   }

   void R_A::R_C_D( const R& R,
                                                               const vector<R_P>& R
                                                             )const
   {
      R_E( R.size() == 1, R_I_A,
                  "deleteauth action should only have one declared authorization" );
      const auto& R = R[0];
      R_E( R.R == R.R, R_I_A,
                  "the owner of the permission to delete needs to be the actor of the declared authorization" );

      const auto& R_M = R_G({R.R, R.R});

      R_E( R_G(R).R( R_M,
                                                  R__.R_G<R_P>().R() ),
                  R_I_A,
                  "updateauth action declares irrelevant authority '${auth}'; minimum authority is ${min}",
                  ("R", R)("min", R_P{R_M.R, R_M.name}) );
   }

   void R_A::R_C_L( const R& R,
                                                             const vector<R_P>& R
                                                           )const
   {
      R_E( R.size() == 1, R_I_A,
                  "link action should only have one declared authorization" );
      const auto& R = R[0];
      R_E( R.R == R.R, R_I_A,
                  "the owner of the linked permission needs to be the actor of the declared authorization" );

      R_E( R.type != R::R_G(),  R_A_V,
                  "Cannot link eosio::updateauth to a minimum permission" );
      R_E( R.type != R::R_G(),  R_A_V,
                  "Cannot link eosio::deleteauth to a minimum permission" );
      R_E( R.type != R::R_G(),    R_A_V,
                  "Cannot link eosio::linkauth to a minimum permission" );
      R_E( R.type != R::R_G(),  R_A_V,
                  "Cannot link eosio::unlinkauth to a minimum permission" );
      R_E( R.type != R::R_G(), R_A_V,
                  "Cannot link eosio::canceldelay to a minimum permission" );

      const auto R_L_P = R_L_M(R.R, R.code, R.type);

      if( !R_L_P ) 
         return;

      R_E( R_G(R).R( R_G({R.R, *R_L_P}),
                                                  R__.R_G<R_P>().R()              ),
                  R_I_A,
                  "link action declares irrelevant authority '${auth}'; minimum authority is ${min}",
                  ("R", R)("min", R_P{R.R, *R_L_P}) );
   }

   void R_A::R_C_U( const R& unlink,
                                                               const vector<R_P>& R
                                                             )const
   {
      R_E( R.size() == 1, R_I_A,
                  "unlink action should only have one declared authorization" );
      const auto& R = R[0];
      R_E( R.R == unlink.R, R_I_A,
                  "the owner of the linked permission needs to be the actor of the declared authorization" );

      const auto R_U_P = R_L_L(unlink.R, unlink.code, unlink.type);
      R_E( R_U_P.R(), R_T,
                  "cannot unlink non-existent permission link of account '${account}' for actions matching '${code}::${action}'",
                  ("account", unlink.R)("code", unlink.code)("action", unlink.type) );

      if( *R_U_P == R::R_E_A )
         return;

      R_E( R_G(R).R( R_G({unlink.R, *R_U_P}),
                                                  R__.R_G<R_P>().R()                  ),
                  R_I_A,
                  "unlink action declares irrelevant authority '${auth}'; minimum authority is ${min}",
                  ("R", R)("min", R_P{unlink.R, *R_U_P}) );
   }

   R::R R_A::R_C_C( const R& R,
                                                                            const vector<R_P>& R
                                                                          )const
   {
      R_E( R.size() == 1, R_I_A,
                  "canceldelay action should only have one declared authorization" );
      const auto& R = R[0];

      R_E( R_G(R).R( R_G(R.R_C),
                                                  R__.R_G<R_P>().R() ),
                  R_I_A,
                  "canceldelay action declares irrelevant authority '${auth}'; specified authority to satisfy is ${min}",
                  ("R", R)("min", R.R_C) );

      const auto& R_T = R.R_T;

      const auto& R_G_T = R__.R().R_G<R_G_T_M>();
      const auto& R_G = R_G_T.R().get<R_B_T>();
      const auto& R = R_G.lower_bound(R_T);
      R_E( R != R_G.end() && R->R == R_A() && R->R_T == R_T,
                  R_T_N,
                 "cannot cancel trx_id=${tid}, there is no deferred transaction with that transaction id",
                 ("tid", R_T) );

      auto R = R::R::R<R>(R->R_P.data(), R->R_P.size());
      bool R = false;
      for( const auto& R : R.R ) {
         for( const auto& R : R.R ) {
            if( R == R.R_C ) {
               R = true;
               break;
            }
         }
         if( R ) break;
      }

      R_E( R, R_A_V,
                  "canceling_auth in canceldelay action was not found as authorization in the original delayed transaction" );

      return (R->R_D - R->R);
   }

   void R_N() {}

   std::function<void()> R_A::R___N{&R_N};

   void
   R_A::R_C( const vector<R>&                R,
                                               const R_F<R_P_K>&     R_P,
                                               const R_F<R_P>&    R_P,
                                               R::R                     R_P,
                                               const std::function<void()>&         R__,
                                               bool                                 R_A_U
                                             )const
   {
      const auto& R = ( static_cast<bool>(R__) ? R__ : R___N );

      auto R_D_M = R::R( R__.R_G_G().R.R_M_T );

      auto R_E_P =  (R_P >= R_D_M) ? R::R::R() : R_P;

      auto R = R_M_A( [&](const R_P& p){ return R_G(p).R; },
                                        R__.R_G_G().R.R_M_A,
                                        R_P,
                                        R_P,
                                        R_E_P,
                                        R
                                      );

      R<R_P, R::R> R_P_T;

      for( const auto& R : R ) {
         bool R_S = false;
         R::R R = R_E_P;

         if( R.R == R::R_S_A ) {
            R_S = true;

            if( R.name == R::R_G() ) {
               R_C_U( R.R_D<R>(), R.R );
            } else if( R.name == R::R_G() ) {
               R_C_D( R.R_D<R>(), R.R );
            } else if( R.name == R::R_G() ) {
               R_C_L( R.R_D<R>(), R.R );
            } else if( R.name == R::R_G() ) {
               R_C_U( R.R_D<R>(), R.R );
            } else if( R.name ==  R::R_G() ) {
               R = std::max( R, R_C_C(R.R_D<R>(), R.R) );
            } else {
               R_S = false;
            }
         }

         for( const auto& R_D : R.R ) {

            R();

            if( !R_S ) {
               auto R_M_P = R_L_M(R_D.R, R.R, R.name);
               if( R_M_P ) { 
                  const auto& R_M = R_G({R_D.R, *R_M_P});
                  R_E( R_G(R_D).R( R_M,
                                                                       R__.R_G<R_P>().R() ),
                              R_I_A,
                              "action declares irrelevant authority '${auth}'; minimum authority is ${min}",
                              ("R", R_D)("min", R_P{R_M.R, R_M.name}) );
               }
            }

            auto R = R_P_T.emplace( R_D, R );
            if( !R.second && R.first->second > R) { 
               R.first->second = R;
            }
         }
      }

      

      
      
      
      
      
      for( const auto& p : R_P_T ) {
         R(); 
         R_E( R.R( p.first, p.second ), R,
                     "transaction declares authority '${auth}', "
                     "but does not have signatures for it under a provided delay of ${provided_delay} ms, "
                     "provided permissions ${provided_permissions}, provided keys ${provided_keys}, "
                     "and a delay max limit of ${delay_max_limit_ms} ms",
                     ("R", p.first)
                     ("provided_delay", R_P.count()/1000)
                     ("provided_permissions", R_P)
                     ("provided_keys", R_P)
                     ("delay_max_limit_ms", R_D_M.count()/1000)
                   );

      }

      if( !R_A_U ) {
         R_E( R.R_A_K(), R_T_I,
                     "transaction bears irrelevant signatures from these keys: ${keys}",
                     ("keys", R.R_U()) );
      }
   }

   void
   R_A::R_C( R_A                         R,
                                               R_P                      R,
                                               const R_F<R_P_K>&     R_P,
                                               const R_F<R_P>&    R_P,
                                               R::R                     R_P,
                                               const std::function<void()>&         R__,
                                               bool                                 R_A_U
                                             )const
   {
      const auto& R = ( static_cast<bool>(R__) ? R__ : R___N );

      auto R_D_M = R::R( R__.R_G_G().R.R_M_T );

      auto R = R_M_A( [&](const R_P& p){ return R_G(p).R; },
                                        R__.R_G_G().R.R_M_A,
                                        R_P,
                                        R_P,
                                        ( R_P >= R_D_M ) ? R::R::R() : R_P,
                                        R
                                      );

      R_E( R.R({R, R}), R,
                  "permission '${auth}' was not satisfied under a provided delay of ${provided_delay} ms, "
                  "provided permissions ${provided_permissions}, provided keys ${provided_keys}, "
                  "and a delay max limit of ${delay_max_limit_ms} ms",
                  ("R", R_P{R, R})
                  ("provided_delay", R_P.count()/1000)
                  ("provided_permissions", R_P)
                  ("provided_keys", R_P)
                  ("delay_max_limit_ms", R_D_M.count()/1000)
                );

      if( !R_A_U ) {
         R_E( R.R_A_K(), R_T_I,
                     "irrelevant keys provided: ${keys}",
                     ("keys", R.R_U()) );
      }
   }

   R_F<R_P_K> R_A::R_G_R( const R& R,
                                                                       const R_F<R_P_K>& R_C,
                                                                       R::R R_P
                                                                     )const
   {
      auto R = R_M_A( [&](const R_P& p){ return R_G(p).R; },
                                        R__.R_G_G().R.R_M_A,
                                        R_C,
                                        {},
                                        R_P,
                                        R___N
                                      );

      for (const auto& R : R.R ) {
         for (const auto& R_D : R.R) {
            R_E( R.R(R_D), R,
                        "transaction declares authority '${auth}', but does not have signatures for it.",
                        ("R", R_D) );
         }
      }

      return R.R_U();
   }

} } 

