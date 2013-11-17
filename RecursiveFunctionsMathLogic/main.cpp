//
//  main.cpp
//  RecursiveFunctionsMathLogic
//
//  Created by  Vladimir Skipor on 11/15/13.
//  Copyright (c) 2013  Vladimir Skipor. All rights reserved.


#include <iostream>
#include <vector>
#include <assert.h>


using namespace std;
typedef unsigned nat;
typedef std::vector<nat> arguments;


struct Z {

    static const nat arg_num = 1;
    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        return 0;
    }

    template<typename... T>
    static nat apl(T... x) {
        arguments args{ x... };
        return apply(args);
    }
};
struct N {
    static const nat arg_num = 1;

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        return args[0] + 1;
    }

    template<typename... T>
    static nat apl(T... x) {
        arguments args = { x... };
    return apply(args);
}
};



template<typename F, typename g, typename... G>
struct S {
    static const nat arg_num = g::arg_num;

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        arguments output = { g::apply(args), G::apply(args)... };
    return F::apply(output);
}

        template<typename... T>
static nat apl(T... x) {
arguments args = { x... };
return apply(args);
}
};

template<nat N, nat M>
struct U {

    static const nat arg_num = N;
    static_assert(N != 0 && M != 0 && N >= M, "invalid template parametrs ");
    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        return args[M-1];
    }

    template<typename... T>
    static nat apl(T... x) {
        arguments args = { x... };
    return apply(args);
}
};



template <typename F, typename G>
struct R {
    static const nat arg_num = F::arg_num + 1;

    static_assert(F::arg_num + 2 == G::arg_num, "invalid template parametrs");

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        nat y = args[arg_num - 1];
        arguments g_args(args.begin(), --args.end());
        nat acc = F::apply(g_args);
        g_args.resize(arg_num + 1);

        for(nat i = 0; i < y; ++i) {
            g_args[arg_num - 1] = i;
            g_args[arg_num] = acc;
            acc = G::apply(g_args);
        }
        return acc;

    }

    template<typename... T>
    static nat apl(T... x) {
        arguments args{ x... };
        return apply(args);
    }
};

template<typename F>
struct M {

    static const nat arg_num = F::arg_num - 1;

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        nat y = 0;
        arguments f_args(args.begin(), args.end());
        f_args.push_back(y);


        while(F::apply(f_args) != 0) {
            f_args[arg_num] = ++y;
        }
        return y;


    }

    template<typename... T>
    static nat apl(T... x) {
        arguments args{ x... };
        return apply(args);
    }
};


template<typename G, typename... T>
void print(T... x) {
arguments args{ x... };
cout << G::apply(args) << endl;
}

typedef S< R<Z,U<3,2> >, U<1,1>, U<1,1> >  DEC;
typedef N INC;
typedef S< N, Z > TRUE;
typedef TRUE ONE;
typedef Z ZERO;
typedef Z FALSE;
typedef S < R < N, S<Z, U<3, 3> > >, U<1,1>, U<1,1> > NOT;
typedef NOT IS_ZERO;
typedef S<NOT, NOT> IS_NOT_ZERO;

typedef S<INC, INC> PLUS_TWO;

typedef S<INC, ONE> TWO;
typedef R< U<1,1>, S<INC, U<3, 3> > > PLUS; //O(x_2)
typedef R< U<1,1>, S<DEC, U<3, 3> > > MINUS;
typedef R< Z, S< PLUS, U<3, 3>, U<3, 1> > > TIMES; // O((x_2)^2)
typedef R< TRUE, S< TIMES, U<3, 3>, U<3, 1> > > POW;
typedef S< DEC, S< M< S<MINUS, U<3,1>, S<TIMES,  U<3, 2>, U<3, 3> > > >, S<INC, U<2, 1> >, U<2, 2> > > DIV; //DIV(0,0) undefined
//typedef S< M< S<MINUS, U<3,1>, S<TIMES,  U<3, 2>, U<3, 3> > > >, S<MINUS, U<2, 1>, S<DEC, U<2,2> > >, U<2, 2> > DIV; // DIV(0,0) = 0
typedef S<MINUS, U<2,1>, S<TIMES, U<2,2>, DIV > > MOD;

typedef S<IS_NOT_ZERO, TIMES> AND;
typedef S<IS_NOT_ZERO, PLUS> OR;
typedef S<AND, OR, S<PLUS, S< NOT, U<2,1> >, S< NOT, U<2,1> > > >  XOR;
typedef S< IS_NOT_ZERO,MINUS > MORE;
typedef S < IS_NOT_ZERO, S<MINUS, U<2,2>, U<2, 1> > >  LESS;
typedef S<AND, S<NOT, MORE>, S<NOT, LESS> > EQUAL;


typedef S<IS_ZERO, MOD> DIVISIBLE;
typedef MOD NOT_DIVISIBLE;
typedef S<
R< S<MORE, U<1,1>, ONE> ,
S< S< AND, S<NOT_DIVISIBLE, U<3,1>, U<3,2> >  , U<3,3> >, U<3,1>, S<PLUS_TWO, U<3,2> >, U<3,3> > >,
U<1,1>, S<DEC, S<DIV, U<1,1>, TWO > >
>  IS_PRIME;
typedef S< R<ZERO, S<PLUS, S<IS_PRIME, U<3,2> >, U<3,3> > >, U<1,1>, S<INC, U<1,1> > > PRIMES_BEFORE;

typedef S < M< S< MORE, U<2,1>, S<PRIMES_BEFORE, U<2,2> > > >, INC>  NTH_PRIME; // O(N^+100500) :((((
typedef  S< DEC, M<S< DIVISIBLE, U<3,2>, S<POW, U<3,1>, U<3,3> > > > >   PLOG;




int main() {
//    cout << Z::apl(5) << endl;
//    cout << N::apl(4) << endl;
//    cout << U<4, 3>::apl(1, 2, 3, 4) << endl;
//    cout << DEC::apl(8) << endl;
//    cout << S< U<6, 3>, Z, Z, Z, Z, Z, Z>::apl (5) << endl;
//    print<DEC>(9);
//    print<TRUE>(5);
//    print<FALSE>(3);
//    print<NOT>(0);
//    print<IS_ZERO>(4);
//    print<PLUS>(4, 7);
//    print<MINUS>(7, 8);
//    print<TIMES> (8, 4);
//    print<POW>(5, 3);
//    print<AND>(0, 1);
//    print<OR>(0, 1);
//    print<XOR>(9,8);
//    print<DIV>(9, 14);
//    print<DIV>(9, 9);
//    print<DIV>(9, 8);
//    print<DIV>(0,0);
//    print<MOD>(15, 3);
//    print<MOD>(14, 3);
//    print<MOD>(13,3);
//    print<MOD>(12,3);
//    print<PLUS_TWO>(3);
//    print<NOT_DIVISIBLE>(5, 2);
//    print<NOT_DIVISIBLE>(6, 2);
//    print<TWO>(4);
//    print<EQUAL>(3, 4);
//    print<EQUAL>(4, 4);
//    print<EQUAL>(5, 4);

    cout << "X PLOG(2,X)" << endl;
    for(nat i = 1; i < 65; i++) {
        cout << i <<' ';
//        print<NTH_PRIME>(i);
        print<PLOG>(2, i);
    }
    cout << "X  NTH_PRIME(X)" << endl;

    for(nat i = 0; i < 15; i++) {
        cout << i <<' ';
        print<NTH_PRIME>(i);
//        print<PLOG>(2, i);
    }
    return 0;
}

