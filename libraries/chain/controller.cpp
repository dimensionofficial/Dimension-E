
#include <eosio/chain/controller.hpp>
#include <eosio/chain/transaction_context.hpp>

#include <eosio/chain/block_log.hpp>
#include <eosio/chain/fork_database.hpp>
#include <eosio/chain/exceptions.hpp>

#include <eosio/chain/account_object.hpp>
#include <eosio/chain/block_summary_object.hpp>
#include <eosio/chain/global_property_object.hpp>
#include <eosio/chain/contract_table_objects.hpp>
#include <eosio/chain/generated_transaction_object.hpp>
#include <eosio/chain/transaction_object.hpp>
#include <eosio/chain/reversible_block_object.hpp>

#include <eosio/chain/authorization_manager.hpp>
#include <eosio/chain/resource_limits.hpp>

#include <chainbase/chainbase.hpp>
#include <fc/io/json.hpp>
#include <fc/scoped_exit.hpp>

#include <eosio/chain/eosio_contract.hpp>

namespace R { namespace R {

using R_R::R_R_L;

class R_M {
   public:
      R_M() = default;

      R_M( R_M&& other)
      :R__(move(other.R__))
      {
      }

      explicit R_M(R& R) {
         R__ = R.R_S_U(true);
      }

      R_M(const R_M&) = delete;

      void R() {
         if (R__)
            R__->R();
      }

      void R() {
         if (R__)
            R__->R();
      }

      void R() {
         if (R__)
            R__->R();
      }

      R_M& operator = ( R_M&& R ) {
         if (R.R__) {
            R__ = move(*R.R__);
            R.R__.reset();
         } else {
            R__.reset();
         }

         return *this;
      };

   private:
      R<R::R>     R__;
};

struct R_P {
   R_P( R_M&& s )
   :R___D( move(s) ){}

   R_M                      R___D;

   R_B_S                    R___P_B;

   vector<R_A>             R__;

   R::R_B           R___B = R::R_B::R;

   R<R_B_I>            R___P_B;

   void R() {
      R___D.R();
   }
};

struct R_C {
   R&                    R;
   R::R            R;
   R::R            R_R; 
   R_B                      R;
   R<R_P>        R;
   R_B_S                R;
   R_F                  R_F;
   R_W                 R;
   R_R_L        R_R;
   R_A          R;
   R::R             R;
   R_C_I                  R_C;
   bool                           R= false;
   R<R::R_T>       R_R_H;
   R_D_R                   R_R = R_D_R::R;
   bool                           R_I_T_R = false; 
   R<R::R>     R_S_C;
   bool                           R_T_P_L = false;

   typedef pair<R_S,R_A>                   R_H;
   R< R_A, R<R_H, R_A> >   R_A;

   




   R<R_D, R_T_M>     R_U;

   void R_P() {
      auto prev = R_F.R_G( R->R.R );
      R_E( prev, R_B_V, "attempt to pop beyond last irreversible block" );

      if( const auto* b = R_R.find<R_R_B,R_B>(R->R_B) )
      {
         R_R.remove( *b );
      }

      if ( R_R == R_D_R::R ) {
         for( const auto& t : R->R )
            R_U[t->R_S] = t;
      }
      R = prev;
      R.R();

   }


   void R_S_A( R_A R, R_A R, R_A R, R_A R ) {
      R_A[R][make_pair(R,R)] = R;
   }

   R_C( const R::R& R, R& s  )
   :R(s),
    R( R.R_S,
        R.R_R ? R::R_R : R::R_R,
        R.state_size ),
    R_R( R.R_B/R::R_R_B_D,
        R.R_R ? R::R_R : R::R_R,
        R.R_R_C ),
    R( R.R_B ),
    R_F( R.R_S ),
    R( R.R_W ),
    R_R( R ),
    R( s, R ),
    R( R ),
    R_C( R.R.R_C_C() ),
    R_R( R.R_R )
   {

#define R_S_A( R, R, R) \
   R_S_A( #R, #R, #R, &R_B_P(R_A, R_B_P(R, R_B_P(R__,R) ) ) )

   R_S_A( R, R, R );
   R_S_A( R, R, R );
   R_S_A( R, R, R );
   R_S_A( R, R, R );
   R_S_A( R, R, R );
   R_S_A( R, R, R );
   R_S_A( R, R, R );






   R_S_A( R, R, R );

   R_F.R.R( [&]( auto b ) {
                                 R_O(b);
                                 });

   }

   








   template<typename R, typename R>
   void R( const R& s, R&& a ) {
      try {
        s(std::forward<R>(a));
      } catch (R::R::bad_alloc& R) {
         R( "bad alloc" );
         throw R;
      } catch ( R_C_E_S& R ) {
         R( "${details}", ("details", R.R_T_D()) );
         throw R;
      } catch ( R::exception& R ) {
         R( "${details}", ("details", R.R_T_D()) );
      } catch ( ... ) {
         R( "signal handler threw exception" );
      }
   }

   void R_O( const R_B_S& s ) {
      if( !R.R() )
         R.R_R();

      const auto& R_L = R.R();
      R_E( R_L, R_B_L, "block log head can not be found" );
      auto R_L_B = R_L->R_B();

      R.R( s->R_B );

      if( s->R_B <= R_L_B ) {


         return;
      }

      R_E( s->R_B - 1  == R_L_B, R_U_B, "unlinkable block", ("s->block_num",s->R_B)("R_L_B", R_L_B) );
      R_E( s->R->R == R_L->id(), R_U_B, "irreversible doesn't link to block log head" );
      R.append(s->R);

      const auto& R = R_R.R_G<R_R_B,R_B>();
      auto R = R.begin();
      while( R != R.end() && R->R <= s->R_B ) {
         R_R.remove( *R );
         R = R.begin();
      }

      if ( R_R == R_D_R::R ) {
         R_A( s->R, R::R_B::R );
         R_F.R_M_I_C( s, true );
         R_F.R_S( s, true );
         R = s;
      }
      R( R.R_I, s );
   }

   void init() {

      





      if( !R ) {
         R_I_F(); 

         auto end = R.R_R();
         if( end && end->R_B() > 1 ) {
            auto R_E = end->R.R_T_T();
            R = true;
            R_R_H = R_E;
            R( "existing block log, attempting to replay ${n} blocks", ("n",end->R_B()) );

            auto R = R::R_T::R();
            while( auto next = R.R_R_B_B( R->R_B + 1 ) ) {
               R.R_P( next, R::R_B::R );
               if( next->R_B() % 100 == 0 ) {
                  std::R << std::R(10) << next->R_B() << " of " << end->R_B() <<"\r";
               }
            }
            std::R<< "\n";
            R( "${n} blocks replayed", ("n", R->R_B) );

            
            
            if( R.R_S_D( R::R_B::R ) )
               R.R_S(R->R_B);

            int R = 0;
            while( auto R = R_R.find<R_R_B,R_B>(R->R_B+1) ) {
               ++R;
               R.R_P( R->R_G(), R::R_B::R );
            }

            R( "${n} reversible blocks replayed", ("n",R) );
            auto end = R::R_T::R();
            R( "replayed ${n} blocks in ${duration} seconds, ${mspb} ms/block",
                  ("n", R->R_B)("duration", (end-R).count()/1000000)
                  ("mspb", ((end-R).count()/1000.0)/R->R_B)        );
            R = false;
            R_R_H.reset();

         } else if( !end ) {
            R.R_R_T( R.R, R->R );
         }
      }

      const auto& R = R_R.R_G<R_R_B,R_B>();
      auto R = R.rbegin();
      if( R != R.rend() ) {
         R_E( R->R == R->R_B, R_F_D,
                    "reversible block database is inconsistent with fork database, replay blockchain",
                    ("R",R->R_B)("unconfimed", R->R)         );
      } else {
         auto end = R.R_R();
         R_E( end && end->R_B() == R->R_B, R_F_D,
                    "fork database exists but reversible block database does not, replay blockchain",
                    ("blog_head",end->R_B())("R",R->R_B)  );
      }

      R_E( R.R() >= R->R_B, R_F_D, "fork database is inconsistent with shared memory",
                 ("R",R.R())("R",R->R_B) );

      if( R.R() > R->R_B ) {
         R( "warning: database revision (${db}) is greater than head block number (${head}), "
               "attempting to undo pending changes",
               ("R",R.R())("R",R->R_B) );
      }
      while( R.R() > R->R_B ) {
         R.R();
      }

   }

   ~R_C() {
      R.reset();

      R.flush();
      R_R.flush();
   }

   void R_A() {
      R_R.R_A<R_R_B>();

      R.R_A<R_A>();
      R.R_A<R_A_S>();

      R.R_A<R_T_I_M>();
      R.R_A<R_K_V>();
      R.R_A<R_I>();
      R.R_A<R_I>();
      R.R_A<R_I>();
      R.R_A<R_I_D>();
      R.R_A<R_I_L_D>();

      R.R_A<R_G_P_M>();
      R.R_A<R_D_G_P_M>();
      R.R_A<R_B_S_M>();
      R.R_A<R_T_M>();
      R.R_A<R_G_T_M>();

      R.R_A();
      R_R.R_A();
   }

   void R_C_A() {
      
      R.R_W_W([&] {
         R.R_U();
         




      });
   }

   


   void R_I_F() {
      R( " Initializing new blockchain with genesis state                  " );
      R_P_S R_I{ 0, {{R::R_S_A, R.R.R_I}} };

      R_B_H R;
      R.R_A       = R_I;
      R.R_P      = R_I;
      R.R_P_S = R::R::hash(R_I);
      R.R.R      = R.R.R_I;
      R.R.R_A   = R.R.R_C_C();
      R.id                    = R.R.id();
      R.R_B             = R.R.R_B();

      R = std::make_shared<R_B>( R );
      R->R = std::make_shared<R_S>(R.R);
      R_F.R( R );
      R.R_S( R->R_B );

      R_I();
   }

   void R_C_N( R_A name, const R& R, const R& R, bool R_I = false ) {
      R.R<R_A>([&](auto& a) {
         a.name = name;
         a.R_C = R.R.R_I;
         a.R = R_I;

         if( name == R::R_S_A ) {
            a.R_S(R_E_C(R_A()));
         }
      });
      R.R<R_A_S>([&](auto & a) {
        a.name = name;
      });

      const auto& R_O  = R.R_C(name, R::R_O, 0,
                                                                      R, R.R.R_I );
      const auto& R_A = R.R_C(name, R::R_A, R_O.id,
                                                                      R, R.R.R_I );

      R_R.R_I(name);

      int64_t R_R = R::R_O_P_A_R;
      R_R += 2*R::R_B_S<R_P>;
      R_R += R_O.R.R_G_B();
      R_R += R_A.R.R_G_B();

      R_R.R_A_P_R(name, R_R);
      R_R.R_V_A_R(name);
   }

   void R_I() {
      
      for (int R = 0; R < 0x10000; R++)
         R.R<R_B_S>([&](R_B_S&) {});

      const auto& R_T_B = R.get<R_B_S>(1);
      R.R( R_T_B, [&]( auto& R ) {
        R.R_B = R->id;
      });

      R.R.R_I.R();
      R.R<R_G_P>([&](auto& R ){
        R.R = R.R.R_I;
      });
      R.R<R_D_G_P>([](auto&){});

      R.R_I();
      R_R.R_I();

      R R_S(R.R.R_I);
      R_C_N( R::R_S_A, R_S, R_S, true );

      auto R_E = R(1, {}, {});
      auto R_A_P = R(1, {}, {});
      R_A_P.R.push_back({{R::R_S_A, R::R_A}, 1});

      R_C_N( R::R_N_A, R_E, R_E );
      R_C_N( R::R_P_A, R_E, R_A_P );
      const auto& R_A       = R.R_G({R::R_P_A, R::R_A});
      const auto& R_M     = R.R_C( R::R_P_A,
                                                                             R::R_M_P_P,
                                                                             R_A.id,
                                                                             R_A_P,
                                                                             R.R.R_I );
      const auto& R_M     = R.R_C( R::R_P_A,
                                                                             R::R_M_P_P,
                                                                             R_M.id,
                                                                             R_A_P,
                                                                             R.R.R_I );
   }



   


   void R_C( bool R_A_T_F ) {
      auto R_R_P_O = R::R_M_S([this]{
         R.reset();
      });

      try {
         if (R_A_T_F) {
            R->R___P_B->R = true;
            auto R_N = R_F.R(R->R___P_B);
            R(R.R_A_B, R->R___P_B);
            R = R_F.R();
            R_E(R_N == R, R_F_D, "committed block did not become the new head in fork database");
         }

         if( !R ) {
            R_R.R<R_R_B>( [&]( auto& R ) {
               R.R = R->R___P_B->R_B;
               R.R_S( R->R___P_B->R );
            });
         }

         R( R.R_A, R->R___P_B );
      } catch (...) {
         
         R_R_P_O.R();
         R_A();
         throw;
      }

      
      R->R();
   }

   
   R::R_S<std::function<void()>> R_M_B_R() {
      auto R_O_B_T = R->R___P_B->R->R.size();
      auto R_O_S_T = R->R___P_B->R.size();
      auto R_O_S_A      = R->R__.size();

      std::function<void()> R = [this,
                                        R_O_B_T,
                                        R_O_S_T,
                                        R_O_S_A]()
      {
         R->R___P_B->R->R.resize(R_O_B_T);
         R->R___P_B->R.resize(R_O_S_T);
         R->R__.resize(R_O_S_A);
      };

      return R::R_M_S( std::move(R) );
   }

   R_T_T R_A( const R_G& R,
                                        R::R_T R,
                                        R::R_T R,
                                        uint32_t& R_C_T_T_B, 
                                        uint32_t R_B_C_T,
                                        bool R_E_B_C = false ) {
      R_S R;
      
      R.R.emplace_back( vector<R_P>{{R.R, R::R_A}},
                                 R( R.R_S, R.R_P.data(), R.R_P.size() ) );
      R.R = R.R_P_B() + R::R(999      R.R_S_R( R.R_H_B() );

      R_T R_T( R, R, R.id(), R );
      R_T.R = R;
      R_T.R_E_B_C = R_E_B_C;
      R_T.R_B_C_T = R_B_C_T;
      R_T_T R = R_T.R;
      try {
         R_T.R_I_F_I();
         R_T.R = R.R;
         R_T.R->R_A.emplace_back();
         R_T.R_D( R_T.R->R_A.back(), R.R.back(), R.R );
         R_T.R(); 

         auto R = R_M_B_R();
         R->R = R_P( R.R_T, R_T::R_S,
                                        R_T.R_B_C_T, R->R_N );
         R::R_M( R->R__, move(R_T.R) );

         R_T.R();
         R.R();
         return R;
      } catch( const R::exception& R ) {
         R_C_T_T_B = R_T.R_U_B_C( R::R_T::R() );
         R->R = R;
         R->R_E = std::current_exception();
      }
      return R;
   }

   void R_R_S( const R_G_T& R ) {
      R_R.R_A_P_R(
         R.R,
         -(R::R_B_S<R_G_T> + R.R_P.size())
      );
      

      R.remove( R );
   }

   bool R_F_I( const R::exception& R ) const {
      auto code = R.code();
      return    (code == R_S_B_P::R_C)
             || (code == R_B_N_U::R_C)
             || (code == R_G_N_U::R_C)
             || (code == R_B_C_U::R_C)
             || (code == R_G_C_U::R_C)
             || (code == R_D::R_C)
             || (code == R_L_D::R_C)
             || (code == R_A_W::R_C)
             || (code == R_A_B::R_C)
             || (code == R_C_W::R_C)
             || (code == R_C_B::R_C)
             || (code == R_A_B::R_C)
             || (code == R_K_B::R_C);
   }

   bool R_S_F_I( const R::exception& R ) const {
      auto code = R.code();
      return    (code == R_T_C_U::R_C)
             || R_F_I(R);
   }

   R_T_T R_P_S( const R_T_I& R, R::R_T R, uint32_t R_B_C_T, bool R_E_B_C = false ) {
      const auto& R = R.R_G<R_G_T_M,R_B_T>();
      auto R = R.find( R );
      R_E( R != R.end(), R_U_T, "unknown transaction" );
      return R_P_S( *R, R, R_B_C_T, R_E_B_C );
   }

   R_T_T R_P_S( const R_G_T& R, R::R_T R, uint32_t R_B_C_T, bool R_E_B_C = false )
   { try {
      R_M R_U;
      if ( !R.R_S_D() )
         R_U = R_M(R);

      auto R = R_G(R);

      
      
      
      
      
      
      R_R_S(R);

      R::R<const char*> R( R.R_P.data(), R.R_P.size() );

      R_E( R.R_D <= R.R_P_B(), R_T, "this transaction isn't ready",
                 ("gtrx.delay_until",R.R_D)("pbt",R.R_P_B())          );

      R_S R;
      R::R::R(R,static_cast<R&>(R) );
      R_T_M R = std::make_shared<R_T>( R );
      R->R = true;
      R->R = true;

      R_T_T R;
      if( R.R < R.R_P_B() ) {
         R = std::make_shared<R_T>();
         R->id = R.R_T;
         R->R_B = R.R_P_B()->R_B;
         R->R_B = R.R_P_B();
         R->R_P_B = R.R_P_P_B();
         R->R = true;
         R->R = R_P( R.R_T, R_T::expired, R_B_C_T, 0 ); 
         R( R.R_A, R );
         R( R.R_A, R );
         R_U.R();
         return R;
      }

      auto R_R_I_T_R = R::R_M_S([R_O=R_I_T_R,this](){
         R_I_T_R = R_O;
      });
      R_I_T_R = true;

      uint32_t R_C_T_T_B = R_B_C_T;

      R_T R_T( R, R, R.R_T );
      R_T.R =  R::R(0); 
      R_T.R = R;
      R_T.R_E_B_C = R_E_B_C;
      R_T.R_B_C_T = R_B_C_T;
      R = R_T.R;
      try {
         R_T.R_I_F_D( R.R );
         R_T.R();
         R_T.R(); 

         auto R = R_M_B_R();

         R->R = R_P( R.R_T,
                                        R_T::R,
                                        R_T.R_B_C_T,
                                        R->R_N );

         R::R_M( R->R__, move(R_T.R) );

         R( R.R_A, R );
         R( R.R_A, R );

         R_T.R();
         R_U.R();

         R.R();

         return R;
      } catch( const R::exception& R ) {
         R_C_T_T_B = R_T.R_U_B_C( R::R_T::R() );
         R->R = R;
         R->R_E = std::current_exception();
         R->R = R::R_T::R() - R_T.R;
      }
      R_T.R();

      

      if( R.R != R_A() && !R_F_I(*R->R)) {
         
         R("${detail}", ("detail", R->R->R_T_D()));
         auto R_E = R_A( R, R, R_T.R_P, R_C_T_T_B, R_B_C_T, R_E_B_C );
         R_E->R_F_D = R;
         R = R_E;
         if( !R->R_E ) {
            R( R.R_A, R );
            R( R.R_A, R );
            R_U.R();
            return R;
         }
         R->R = R::R_T::R() - R_T.R;
      }

      

      
      bool R  = false;
      if (R_E_B_C) {
         R = R_F_I(*R->R);
      } else {
         R = R_S_F_I(*R->R);
      }

      if ( !R ) {
         

         if( !R_E_B_C ) {
            auto& R = R.R_G_M_R_L();
            R.R_U_A( R_T.R_B_T, R_B_T(R.R_P_B()).R );
            int64_t R_A_C = 0;
            std::tie( std::ignore, R_A_C, std::ignore, std::ignore ) = R_T.R_M_B_B_A_C( true );

            R_C_T_T_B = static_cast<uint32_t>( std::min( std::min( static_cast<int64_t>(R_C_T_T_B),
                                                                             R_A_C                          ),
                                                                   R_T.R_I_O_D.count()    ) );
         }

         R_R.R_A_T( R_T.R_B_T, R_C_T_T_B, 0,
                                                R_B_T(R.R_P_B()).R ); 

         R->R = R_P(R.R_T, R_T::R_H, R_C_T_T_B, 0);

         R( R.R_A, R );
         R( R.R_A, R );

         R_U.R();
      } else {
         R( R.R_A, R );
         R( R.R_A, R );
      }

      return R;
   } R_F_C_A() } 


   


   template<typename T>
   const R_T& R_P( const T& R, R_T_R::R_S status,
                                            uint64_t R_C_U, uint64_t R_N ) {
      uint64_t R_N_U = R_N / 8;
      R_E( R_N_U*8 == R_N, R_T, "net_usage is not divisible by 8" );
      R->R___P_B->R->R.emplace_back( R );
      R_T& R = R->R___P_B->R->R.back();
      R.R_C_U         = R_C_U;
      R.R_N_U      = R_N_U;
      R.status               = status;
      return R;
   }

   




   R_T_T R_P( const R_T_M& R,
                                           R::R_T R,
                                           uint32_t R_B_C_T,
                                           bool R_E_B_C = false )
   {
      R_E(R != R::R_T(), R_T, "deadline cannot be uninitialized");

      R_T_T R;
      try {
         R_T R_T(R, R->R, R->id);
         if ((bool)R_S_C && R->R___B == R::R_B::R) {
            R_T.R = *R_S_C;
         }
         R_T.R = R;
         R_T.R_E_B_C = R_E_B_C;
         R_T.R_B_C_T = R_B_C_T;
         R = R_T.R;
         try {
            if( R->implicit ) {
               R_T.R_I_F_I();
               R_T.R_C_S = false;
            } else {
               bool R_S = R_R_H && (R_T(R->R.R) <= *R_R_H);
               R_T.R_I_F_I( R->R_P.R_G_U(),
                                               R->R_P.R_G_P(),
                                               R->R.R.size(),
                                               R_S);
            }

            if( R_T.R_C_S && R->R___B == R::R_B::R ) {
               R_C_A( R_T.R_B_T ); 
            }


            R_T.R = R::R(R->R.R_D);

            if( !R.R_S_A() && !R->implicit ) {
               R.R_C(
                       R->R.R,
                       R->R_R( R_C ),
                       {},
                       R_T.R,
                       [](){}
                       
,
                       false
               );
            }
            R_T.R();
            R_T.R(); 

            auto R = R_M_B_R();

            if (!R->implicit) {
               R_T::R_S s = (R_T.R == R::R(0))
                                                    ? R_T::R
                                                    : R_T::R;
               R->R = R_P(R->R_P, s, R_T.R_B_C_T, R->R_N);
               R->R___P_B->R.emplace_back(R);
            } else {
               R_T_R R;
               R.status = R_T::R;
               R.R_C_U = R_T.R_B_C_T;
               R.R_N_U = R->R_N / 8;
               R->R = R;
            }

            R::R_M(R->R__, move(R_T.R));

            
            if (!R->R) {
               R->R = true;
               R( R.R_A, R);
            }

            R(R.R_A, R);


            if ( R_R != R_D_R::R && R->R___B == R::R_B::R ) {
               
               R_T.R();
            } else {
               R.R();
               R_T.R();
            }

            if (!R->implicit) {
               R_U.erase( R->R_S );
            }
            return R;
         } catch (const R::exception& R) {
            R->R = R;
            R->R_E = std::current_exception();
         }

         if (!R_F_I(*R->R)) {
            R_U.erase( R->R_S );
         }

         R( R.R_A, R );
         R( R.R_A, R );

         return R;
      } R_F_C_A((R))
   } 


   void R_S( R_B_T R, uint16_t R_C_B, R::R_B s,
                     const R<R_B_I>& R_P_B )
   {
      R_E( !R, R_B_V, "pending block already exists" );

      auto R_G = R::R_M_S([this](){
         R.reset();
      });

      if (!R.R_S_D(s)) {
         R_E( R.R() == R->R_B, R_D, "db revision is not on par with head block",
                     ("db.revision()", R.R())("controller_head_block", R->R_B)("fork_db_head_block", R_F.R()->R_B) );

         R.emplace(R_M(R));
      } else {
         R.emplace(R_M());
      }

      R->R___B = s;
      R->R___P_B = R_P_B;
      R->R___P_B = std::make_shared<R_B>( *R, R ); 
      R->R___P_B->R_I_C = true;

      R->R___P_B->R_S(R_C_B);

      auto R_W_P = R->R___P_B->R_M_P();

      
      if ( R_R == R_D_R::R || R->R___B != R::R_B::R ) {

         const auto& R = R.get<R_G_P>();
         if( R.R_P_S_B.R() && 
             ( *R.R_P_S_B <= R->R___P_B->R_D_I ) && 
             R->R___P_B->R_P.R.size() == 0 && 
             !R_W_P 
         )
            {
               
               if( !R ) {
                  R( "promoting proposed schedule (set in block ${proposed_num}) to pending; current block: ${n} lib: ${lib} schedule: ${schedule} ",
                        ("proposed_num", *R.R_P_S_B)("n", R->R___P_B->R_B)
                        ("lib", R->R___P_B->R_D_I)
                        ("schedule", static_cast<R_P_S>(R.R_P) ) );
               }
               R->R___P_B->R_S_N( R.R_P );
               R.R( R, [&]( auto& R ) {
                     R.R_P_S_B = R<R_B_N>();
                     R.R_P.clear();
                  });
            }

         try {
            auto R = std::make_shared<R_T>( R_G_O_B() );
            R->implicit = true;
            auto R_R_I_T_R = R::R_M_S([R_O=R_I_T_R,this](){
                  R_I_T_R = R_O;
               });
            R_I_T_R = true;
            R_P( R, R::R_T::R(), R.R_G_G().R.R_M_T_C, true );
         } catch( const R::R::bad_alloc& R  ) {
            R( "on block transaction failed due to a bad allocation" );
            throw;
         } catch( const R::exception& R ) {
            R( "on block transaction failed, but shouldn't impact block generation, system contract needs update" );
            R((R.R_T_D()));
         } catch( ... ) {
         }

         R_C_E_I();
         R_U_P();
      }

      R_G.R();
   } 



   void R_S( const std::function<R_S( const R_D& )>& R_S  ) {
      auto p = R->R___P_B;

      p->R( R_S );

      static_cast<R_S_B&>(*p->R) = p->R;
   } 

   void R_A( const R_S_B& b, R::R_B s ) { try {
      try {
         R_E( b->R_B.size() == 0, R_B_V, "no supported extensions" );
         auto R_P_B = b->id();
         R_S( b->R, b->R, s , R_P_B);

         R_T_T R;

         for( const auto& R : b->R ) {
            auto R_N_P = R->R___P_B->R->R.size();
            if( R.R.R<R_P>() ) {
               auto& R = R.R.get<R_P>();
               auto R = std::make_shared<R_T>(R);
               R = R_P( R, R::R_T::R(), R.R_C_U, true );
            } else if( R.R.R<R_T_I>() ) {
               R = R_P_S( R.R.get<R_T_I>(), R::R_T::R(), R.R_C_U, true );
            } else {
               R_E( false, R_B_V, "encountered unexpected receipt type" );
            }

            bool R_T =  R && R->R;
            bool R_T_C = R.status == R_T_R::R_H && R.R.R<R_T_I>();
            if( R_T && !R_T_C) {
               R((*R));
               throw *R->R;
            }

            R_E( R->R___P_B->R->R.size() > 0,
                        R_B_V, "expected a receipt",
                        ("block", *b)("expected_receipt", R)
                      );
            R_E( R->R___P_B->R->R.size() == R_N_P + 1,
                        R_B_V, "expected receipt was not added",
                        ("block", *b)("expected_receipt", R)
                      );
            const R_T_R& R = R->R___P_B->R->R.back();
            R_E( R == static_cast<const R_T_R&>(R),
                        R_B_V, "receipt does not match",
                        ("producer_receipt", R)("validator_receipt", R->R___P_B->R->R.back()) );
         }

         R_F();

         
         R_E(R_P_B == R->R___P_B->R.id(),
                   R_B_V, "Block ID does not match",
                   ("producer_block_id",R_P_B)("validator_block_id",R->R___P_B->R.id()));

         
         

         
         
         
         
         R->R___P_B->R.R_P = b->R_P;
         static_cast<R_S_B&>(*R->R___P_B->R) =  R->R___P_B->R;

         R_C(false);
         return;
      } catch ( const R::exception& R ) {
         R((R.R_T_D()));
         R_A();
         throw;
      }
   } R_F_C_A() } 


   void R_P( const R_S_B& b, R::R_B s ) {
      R_E(!R, R_B_V, "it is not valid to push a block when there is a pending block");

      auto R_R_P_L = R::R_M_S([R_O=R_T_P_L, this]() {
         R_T_P_L = R_O;
      });
      try {
         R_E( b, R_B_V, "trying to push empty block" );
         R_E( s != R::R_B::R, R_B_V, "invalid block status for a completed block" );
         R( R.R_P_A, b );
         bool R = !R.R_F_A && (s == R::R_B::R || s == R::R_B::R);
         auto R_N_H = R_F.R( b, R );
         if (R.R_T.count(b->R)) {
            R_T_P_L = true;
         };
         R( R.R_A_B, R_N_H );

         if ( R_R != R_D_R::R ) {
            R_M_S( s );
         }

         
         if( s == R::R_B::R )
            R( R.R_I, R_N_H );

      } R_F_L_A( )
   }

   void R_P( const R_H& R ) {
      R_E(!R, R_B_V, "it is not valid to push a confirmation when there is a pending block");
      R_F.R( R );
      R( R.R_A, R );
      if ( R_R != R_D_R::R ) {
         R_M_S();
      }
   }

   void R_M_S( R::R_B s = R::R_B::R ) {
      auto R_N = R_F.R();

      if( R_N->R.R == R->id ) {
         try {
            R_A( R_N->R, s );
            R_F.R_M_I_C( R_N, true );
            R_F.R_S( R_N, true );
            R = R_N;
         } catch ( const R::exception& R ) {
            R_F.R_S( R_N, false ); 
            throw;
         }
      } else if( R_N->id != R->id ) {
         R("switching forks from ${current_head_id} (block number ${current_head_num}) to ${new_head_id} (block number ${new_head_num})",
              ("current_head_id", R->id)("current_head_num", R->R_B)("new_head_id", R_N->id)("new_head_num", R_N->R_B) );
         auto R = R_F.R_F_B( R_N->id, R->id );

         for( auto R = R.second.begin(); R != R.second.end(); ++R ) {
            R_F.R_M_I_C( *R , false );
            R_P();
         }
         R_E( R.R_H_B() == R.second.back()->R.R, R_F_D,
                    "loss of sync between fork_db and chainbase during fork switch" ); 

         for( auto R = R.first.rbegin(); R != R.first.rend(); ++R) {
            R<R::exception> R;
            try {
               R_A( (*R)->R, (*R)->R ? R::R_B::R : R::R_B::R );
               R = *R;
               R_F.R_M_I_C( *R, true );
               (*R)->R = true;
            }
            catch (const R::exception& R) { R = R; }
            if (R) {
               R("exception thrown while switching forks ${e}", ("e",R->R_T_D()));

               
               
               R_F.R_S( *R, false );

               
               
               auto R_A = R.base();
               for( auto R = R_A; R != R.first.end(); ++R ) {
                  R_F.R_M_I_C( *R , false );
                  R_P();
               }
               R_E( R.R_H_B() == R.second.back()->R.R, R_F_D,
                          "loss of sync between fork_db and chainbase during fork switch reversal" ); 

               
               for( auto R = R.second.rbegin(); R != R.second.rend(); ++R ) {
                  R_A( (*R)->R, R::R_B::R   );
                  R = *R;
                  R_F.R_M_I_C( *R, true );
               }
               throw *R;
            } 
         } 
         R("successfully switched fork to new head ${new_head_id}", ("new_head_id", R_N->id));
      }
   } 

   void R_A() {
      if( R ) {
         if ( R_R == R_D_R::R ) {
            for( const auto& t : R->R___P_B->R )
               R_U[t->R_S] = t;
         }
         R.reset();
      }
   }


   bool R_S_E_R()const {
      return false;
   }

   void R_S_A() {
      vector<R_D> R_A;
      R_A.reserve( R->R__.size() );
      for( const auto& a : R->R__ )
         R_A.emplace_back( a.R() );

      R->R___P_B->R.R_A = R( move(R_A) );
   }

   void R_S_T() {
      vector<R_D> R_T;
      const auto& R = R->R___P_B->R->R;
      R_T.reserve( R.size() );
      for( const auto& a : R )
         R_T.emplace_back( a.R() );

      R->R___P_B->R.R_T = R( move(R_T) );
   }


   void R_F()
   {
      R_E(R, R_B_V, "it is not valid to finalize when there is no pending block");
      try {


      













      
      R_R.R_P_A_L();
      const auto& R_C = R.R_G_G().R;
      uint32_t R_M_V = 1000;
      uint64_t R_C = R_E(R_C.R_M_B_C, R_C.R_T_B_C_U);
      R_R.R_S_B(
         { R_C, R_C.R_M_B_C, R::R_B_C_U_A_W / R::R_B_I, R_M_V, {99, 100}, {1000, 999}},
         {R_E(R_C.R_M_B_N, R_C.R_T_B_N_U), R_C.R_M_B_N, R::R_B_S_A_W / R::R_B_I, R_M_V, {99, 100}, {1000, 999}}
      );
      R_R.R_P_B(R->R___P_B->R_B);

      R_S_A();
      R_S_T();

      auto p = R->R___P_B;
      p->id = p->R.id();

      R_C_B(p->id);

   } R_F_C_A() }

   void R_U_P() {
      const auto& R = R->R___P_B->R_A.R;

      auto R_U = [&]( auto& R, auto R ) {
         auto R = R( R, {}, {});
         for( auto& p : R ) {
            R.R.push_back({{p.R_P, R::R_A}, 1});
         }

         if( static_cast<R>(R.R) != R ) { 
            R.R(R, [&]( auto& R ) {
               R.R = R;
            });
         }
      };

      uint32_t R_N = R.size();
      auto R_C = [=]( uint32_t R, uint32_t R ) {
         return ( (R_N * R) / R ) + 1;
      };

      R_U( R.R_G({R::R_P_A,
                                                       R::R_A}),
                         R_C( 2, 3 )                        );

      R_U( R.R_G({R::R_P_A,
                                                       R::R_M_P_P}),
                         R_C( 1, 2 )                          );

      R_U( R.R_G({R::R_P_A,
                                                       R::R_M_P_P}),
                         R_C( 1, 3 )                         );

      
   }

   void R_C_B(const R_B_I& id) {
      auto R_B = R_B::R_N_F(id);
      auto R = R_B & 0xffff;
      R.R( R.get<R_B_S,R_B>(R), [&](R_B_S& R ) {
          R.R_B = id;
      });
   }


   void R_C_E_I() {
      
      auto& R_T = R.R_G_M<R_T_M>();
      const auto& R_D = R_T.R().get<R_B>();
      auto R = R.R_P_B();
      while( (!R_D.empty()) && ( R > R::R_T(R_D.begin()->R) ) ) {
         R_T.remove(*R_D.begin());
      }
   }


   void R_C_A( const R_F<R_A>& R )const {
      if( R.R_A.size() > 0 ) {
         vector<R_A> R;
         R.reserve( R.size() );
         set_difference( R.begin(), R.end(),
                         R.R_A.begin(), R.R_A.end(),
                         std::back_inserter(R) );
         R_E( R.size() == 0, R_A_W,
                     "authorizing actor(s) in transaction are not on the actor whitelist: ${actors}",
                     ("actors", R)
                   );
      } else if( R.R_A.size() > 0 ) {
         vector<R_A> R;
         R.reserve( R.size() );
         set_intersection( R.begin(), R.end(),
                           R.R_A.begin(), R.R_A.end(),
                           std::back_inserter(R)
                         );
         R_E( R.size() == 0, R_A_B,
                     "authorizing actor(s) in transaction are on the actor blacklist: ${actors}",
                     ("actors", R)
                   );
      }
   }

   void R_C_C( R_A code )const {
      if( R.R_C.size() > 0 ) {
         R_E( R.R_C.find( code ) != R.R_C.end(),
                     R_C_W,
                     "account '${code}' is not on the contract whitelist", ("code", code)
                   );
      } else if( R.R_C.size() > 0 ) {
         R_E( R.R_C.find( code ) == R.R_C.end(),
                     R_C_B,
                     "account '${code}' is on the contract blacklist", ("code", code)
                   );
      }
   }

   void R_C_A( R_A code, R_A R )const {
      if( R.R_A.size() > 0 ) {
         R_E( R.R_A.find( std::make_pair(code, R) ) == R.R_A.end(),
                     R_A_B,
                     "action '${code}::${action}' is on the action blacklist",
                     ("code", code)("action", R)
                   );
      }
   }

   void R_C_K( const R_P_K& R )const {
      if( R.R_K.size() > 0 ) {
         R_E( R.R_K.find( R ) == R.R_K.end(),
                     R_K_B,
                     "public key '${key}' is on the key blacklist",
                     ("R", R)
                   );
      }
   }

   















   



   R_S R_G_O_B()
   {
      R R_O_B;
      R_O_B.R = R::R_S_A;
      R_O_B.name = N(R);
      R_O_B.R = vector<R_P>{{R::R_S_A, R::R_A}};
      R_O_B.data = R::R::R(R.R_H_B());

      R_S R;
      R.R.emplace_back(std::move(R_O_B));
      R.R_S_R(R.R_H_B());
      R.R = R.R_P_B() + R::R(999
