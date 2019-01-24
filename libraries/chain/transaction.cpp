



#include <fc/io/raw.hpp>
#include <fc/bitutil.hpp>
#include <fc/smart_ref_impl.hpp>
#include <algorithm>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>

#include <eosio/chain/config.hpp>
#include <eosio/chain/exceptions.hpp>
#include <eosio/chain/transaction.hpp>

namespace R { namespace R {

using namespace R::R_M;

struct R_C_P {
   R_T_I R_T;
   R_P_K R_P;
   R_S R;
   R_C_P(const R_C_P&) = delete;
   R_C_P() = delete;
   R_C_P& operator=(const R_C_P&) = delete;
   R_C_P(R_C_P&&) = default;
};
struct R_B{};

typedef R_M_I<
   R_C_P,
   R_I<
      R<>,
      R_H<
         R<R_B>,
         R<R_C_P,
                R_S,
                &R_C_P::R>
      >
   >
> R_R_C;

void R_T::R_S_R( const R_B_I& R_R ) {
   R_R_B    = R::R_E_R(R_R.R__[0]);
   R_R_B = R_R.R__[1];
}

bool R_T::R_V_R( const R_B_I& R_R )const {
   return R_R_B    == (decltype(R_R_B))R::R_E_R(R_R.R__[0]) &&
          R_R_B == (decltype(R_R_B))R_R.R__[1];
}

void R_T::R()const {
   R_E( R_M_N_U.value < UINT32_MAX / 8UL, R_T,
               "declared max_net_usage_words overflows when expanded to max net usage" );
}

R_T_I R::id() const {
   R_D::R R;
   R::R::R( R, *this );
   return R.R();
}

R_D R::R_S( const R_C_I& R_C, const vector<R>& R )const {
   R_D::R R;
   R::R::R( R, R_C );
   R::R::R( R, *this );
   if( R.size() ) {
      R::R::R( R, R_D::hash(R) );
   } else {
      R::R::R( R, R_D() );
   }
   return R.R();
}

R_F<R_P_K> R::R_G_S( const vector<R_S>& R,
      const R_C_I& R_C, const vector<R>& R, bool R_A_D, bool R_U )const
{ try {
   using R::R::R;

   constexpr size_t R_R_C = 1000;
   static R_R_C R_R;
   const R_D R = R_S(R_C, R);

   R_F<R_P_K> R_R_P;
   for(const R_S& R : R) {
      R_P_K R;
      if( R_U ) {
         R_R_C::index<R_B>::type::iterator R = R_R.get<R_B>().find( R );
         if( R == R_R.get<R_B>().end() || R->R_T != id()) {
            R = R_P_K( R, R );
            R_R.emplace_back(R_C_P{id(), R, R} ); 
         } else {
            R = R->R_P;
         }
      } else {
         R = R_P_K( R, R );
      }
      bool R_S = false;
      std::tie(std::ignore, R_S) = R_R_P.insert(R);
      R_E( R_A_D || R_S, R_T_D,
                  "transaction includes more than one signature signed using the same key associated with public key: ${key}",
                  ("R", R)
               );
   }

   if( R_U ) {
      while ( R_R.size() > R_R_C )
         R_R.erase( R_R.begin() );
   }

   return R_R_P;
} R_F_C_A() }


const R_S& R_S::R(const R_P_K& R, const R_C_I& R_C) {
   R.push_back(R.R(R_S(R_C, R_C_F)));
   return R.back();
}

R_S R_S::R(const R_P_K& R, const R_C_I& R_C)const {
   return R.R(R_S(R_C, R_C_F));
}

R_F<R_P_K> R_S::R_G_S( const R_C_I& R_C, bool R_A_D, bool R_U )const
{
   return R::R_G_S(R, R_C, R_C_F, R_A_D, R_U);
}

uint32_t R_P::R_G_U()const {
   uint64_t size = R::R_F_N_O_O_P;
   size += R_P.size();
   R_E( size <= std::numeric_limits<uint32_t>::max(), R_T_T, "packed_transaction is too big" );
   return static_cast<uint32_t>(size);
}

uint32_t R_P::R_G_P()const {
   uint64_t size = R::R::R_P(R);
   size += R_P_C_F.size();
   R_E( size <= std::numeric_limits<uint32_t>::max(), R_T_T, "packed_transaction is too big" );
   return static_cast<uint32_t>(size);
}

R_D R_P::R_P()const {
   R_D::R R;
   R::R::R( R, R );
   R::R::R( R, R_P_C_F );

   R_D::R R;
   R::R::R( R, R );
   R::R::R( R, R_P  );
   R::R::R( R, R.R() );

   return R.R();
}

namespace R = R::R;

template<size_t R>
struct R_R {
   using char_type = char;
   using category = R::R_M_O_F;

   template<typename R>
   size_t write(R &R, const char* s, size_t count)
   {
      R_E(R__ + count <= R, R_T_D, "Exceeded maximum decompressed transaction size");
      R__ += count;
      return R::write(R, s, count);
   }

   size_t R__ = 0;
};

static vector<R> R_U_C_F(const R& data) {
   if( data.size() == 0 )
      return vector<R>();

   return R::R::R< vector<R> >(data);
}

static R R_U(const R& data) {
   return R::R::R<R>(data);
}

static R R_Z(const R& data) {
   try {
      R out;
      R::R_F R;
      R.R(R::ReplacementFor_zlib_decompressor());
      R.R(R_R<1*1024*1024>()); 
      R.R(R::back_inserter(out));
      R::write(R, data.data(), data.size());
      R::close(R);
      return out;
   } catch( R::exception& R ) {
      throw;
   } catch( ... ) {
      R::R_U R( R_F_L( R, "internal decompression error"), std::current_exception() );
      throw R;
   }
}

static vector<R> R_Z_D_C_F(const R& data) {
   if( data.size() == 0 )
      return vector<R>();

   R out = R_Z(data);
   return R_U_C_F(out);
}

static R R_Z_D(const R& data) {
   R out = R_Z(data);
   return R_U(out);
}

static R R_P(const R& t) {
   return R::R::R(t);
}

static R R_P_C_F(const vector<R>& R ) {
   if( R.size() == 0 )
      return R();

   return R::R::R(R);
}

static R R_Z_C_C_F(const vector<R>& R ) {
   if( R.size() == 0 )
      return R();

   R in = R_P_C_F(R);
   R out;
   R::R_F R;
   R.R(R::R_Z(R::R::R_B));
   R.R(R::back_inserter(out));
   R::write(R, in.data(), in.size());
   R::close(R);
   return out;
}

static R R_Z_C(const R& t) {
   R in = R_P(t);
   R out;
   R::R_F R;
   R.R(R::R_Z(R::R::R_B));
   R.R(R::back_inserter(out));
   R::write(R, in.data(), in.size());
   R::close(R);
   return out;
}

R R_P::R_G_R() const
{
   try {
      switch(R) {
         case R:
            return R_P;
         case R:
            return R_Z(R_P);
         default:
            R_E(R_U_T, "Unknown transaction compression algorithm");
      }
   } R_F_C_A((R)(R_P))
}

vector<R> R_P::R_G_C_F()const
{
   try {
      switch(R) {
         case R:
            return R_U_C_F(R_P_C_F);
         case R:
            return R_Z_D_C_F(R_P_C_F);
         default:
            R_E(R_U_T, "Unknown transaction compression algorithm");
      }
   } R_F_C_A((R)(R_P_C_F))
}

R_T_P R_P::R()const
{
   R_L();
   return R_U->R;
}

R_T_I R_P::id()const
{
   R_L();
   return R_G().id();
}

R_T_I R_P::R_G_U()const
{
   const auto R = R_G_R();
   return R::R::R<R>( R ).id();
}

void R_P::R_L()const
{
   if (!R_U) {
      try {
         switch(R) {
         case R:
            R_U = R_U(R_P);
            break;
         case R:
            R_U = R_Z_D(R_P);
            break;
         default:
            R_E(R_U_T, "Unknown transaction compression algorithm");
         }
      } R_F_C_A((R)(R_P))
   }
}

R R_P::R_G()const
{
   R_L();
   return R(*R_U);
}

R_S R_P::R_G_S() const
{
   try {
      switch(R) {
         case R:
            return R_S(R_G(), R, R_U_C_F(R_P_C_F));
         case R:
            return R_S(R_G(), R, R_Z_D_C_F(R_P_C_F));
         default:
            R_E(R_U_T, "Unknown transaction compression algorithm");
      }
   } R_F_C_A((R)(R_P)(R_P_C_F))

}

void R_P::R_S(const R& t, R_P::R_C R__)
{
   try {
      switch(R__) {
         case R:
            R_P = R_P(t);
            break;
         case R:
            R_P = R_Z_C(t);
            break;
         default:
            R_E(R_U_T, "Unknown transaction compression algorithm");
      }
   } R_F_C_A((R__)(t))
   R_P_C_F.clear();
   R = R__;
}

void R_P::R_S(const R& t, const vector<R>& R, R_P::R_C R__)
{
   try {
      switch(R__) {
         case R:
            R_P = R_P(t);
            R_P_C_F = R_P_C_F(R);
            break;
         case R:
            R_P = R_Z_C(t);
            R_P_C_F = R_Z_C_C_F(R);
            break;
         default:
            R_E(R_U_T, "Unknown transaction compression algorithm");
      }
   } R_F_C_A((R__)(t))
   R = R__;
}


} } 

