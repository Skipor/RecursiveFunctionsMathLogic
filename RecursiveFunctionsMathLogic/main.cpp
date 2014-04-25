//
//  main.cpp
//  RecursiveFunctionsMathLogic
//
//  Created by  Vladimir Skipor on 11/15/13.
//  Copyright (c) 2013  Vladimir Skipor. All rights reserved.


#include <iostream>
#include <vector>
#include <assert.h>
#import <stack>
#import <cmath>


using namespace std;
typedef long long nat;
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
//        cout <<  "args "  << args.size() << ' ' << arg_num << endl;
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



template <int argNum>
struct Base {
public:
    static const nat arg_num = argNum;


};

struct PLOG : Base<2> {

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);

        nat x = args[1];
        nat p = args[0];
        nat couter = 0;
        while (!(x % p)) {
            x /= p;
            couter ++;
        }
        return couter;

    }

};

struct DIV : Base<2> {

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);

        nat y = args[1];
        nat x = args[0];

        return x / y;

    }

};

struct PLUS : Base<2> {

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        nat y = args[1];
        nat x = args[0];

        return x + y;

    }

};

struct TIMES : Base<2> {

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        nat y = args[1];
        nat x = args[0];

        return x * y;

    }

};

struct MOD : Base<2> {

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        nat y = args[1];
        nat x = args[0];

        return x % y;

    }

};

struct MINUS : Base<2> {

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        nat y = args[1];
        nat x = args[0];

        return x - y < 0 ? 0: x -y;

    }

};

struct DEC : Base<1> {

    static nat apply(arguments const & args) {
        assert(args.size() == arg_num);
        nat x = args[0];

        return x ? x - 1: 0;

    }

};




//typedef S< R<Z,U<3,2> >, U<1,1>, U<1,1> >  DEC;
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
typedef S<INC, TWO> THREE;
typedef S<INC, S<INC, THREE> > FIVE;
//typedef R< U<1,1>, S<INC, U<3, 3> > > PLUS; //O(x_2)
//typedef R< U<1,1>, S<DEC, U<3, 3> > > MINUS;
//typedef R< Z, S< PLUS, U<3, 3>, U<3, 1> > > TIMES; // O((x_2)^2)
typedef R< TRUE, S< TIMES, U<3, 3>, U<3, 1> > > POW;
//typedef S< DEC, S< M< S<MINUS, U<3,1>, S<TIMES,  U<3, 2>, U<3, 3> > > >, S<INC, U<2, 1> >, U<2, 2> > > DIV; //DIV(0,0) undefined
//typedef S< M< S<MINUS, U<3,1>, S<TIMES,  U<3, 2>, U<3, 3> > > >, S<MINUS, U<2, 1>, S<DEC, U<2,2> > >, U<2, 2> > DIV; // DIV(0,0) = 0
//typedef S<MINUS, U<2,1>, S<TIMES, U<2,2>, DIV > > MOD;

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

typedef S<S<INC, PLUS>, U<1, 1>, M <S<NOT, S < IS_PRIME, S<INC, PLUS> > > > > NEXT_PRIME;
typedef S<S<DEC, MINUS>, U<1, 1>, M <S<NOT, S < IS_PRIME, S<DEC, MINUS> > > > > PREV_PRIME;
typedef S<R<TWO, S< NEXT_PRIME, U<3, 3> > >, U<1, 1>, U<1,1> > NTH_PRIME;

//typedef S < M< S< MORE, U<2,1>, S<PRIMES_BEFORE, U<2,2> > > >, INC>  NTH_PRIME; // O(N^+100500) :((((
//typedef  S< DEC, M<S< DIVISIBLE, U<3,2>, S<POW, U<3,1>, U<3,3> > > > >   PLOG;


//template <typename Condition, typename Then , typename Else>
//struct IF : S < R< Then, Else>, U<n, 1>, U<n, 2> ..., S<NOT, Condition> > this if is not lasy - then branch always counting
// Else n + 2 arguments, where args'[n + 1] = 1, args'[n + 2] = Then(args)
// Else = S<CorrectElse, U<n + 2, 1>, U<n + 2, 2> ... U<n + 2, n> >


typedef S<PLOG, TWO, U<1, 1> > STACK_SIZE;
typedef  S< NTH_PRIME, STACK_SIZE > TOP_STACK_PRIME; //
typedef S<DIV, U<1, 1>, TWO> DEC_SIZE;
typedef S<TIMES, U<1,1>, TWO> INC_SIZE;
////typedef  S< PREV_PRIME, S< NTH_PRIME, STACK_SIZE> > TOP_STACK_PRIME; // infinite loop on empty stack
typedef S< PLOG,  TOP_STACK_PRIME, U<1, 1> >  ULT; //head, peek, last, ultimate
typedef S< PLOG,  S<PREV_PRIME, TOP_STACK_PRIME>, U<1,1> > PENULT; // before head, penultimame
typedef S< DEC_SIZE, S< DIV, U<1, 1>, S< POW, TOP_STACK_PRIME, ULT >  > > POP;
typedef S < S<TIMES, U<2, 1>, S<POW, S< TOP_STACK_PRIME, U<2, 1> > , U<2, 2> > >, S< INC_SIZE, U<2, 1> >, U<2, 2> > PUSH;
//typedef S<NOT_DIVISIBLE, U<1,1>, FIVE> READY;
typedef S<EQUAL, STACK_SIZE, ONE> READY;
typedef S<MORE, STACK_SIZE, ONE> NOT_READY;
typedef ONE EMPTY_STACK;

typedef S<PUSH, S<POP, POP>, S<INC, ULT>>ACKERMANN_FIRST;
typedef S<PUSH, S<PUSH, S<POP, POP>, S<DEC, PENULT> >, ONE> ACKERMANN_SECOND;
typedef S<PUSH, S<PUSH, S<PUSH, S<POP, POP>, S<DEC, PENULT> > , PENULT > , S<DEC, ULT>  > ACKERMANN_THIRD;


typedef S<NOT, PENULT> FIRST_CASE;
typedef S<NOT, ULT> SECOND_CASE;

typedef S< S < R< ACKERMANN_SECOND, S<ACKERMANN_THIRD, U<3, 1> > >, U<1, 1> , S<NOT, SECOND_CASE> > , U<3, 1> > ACKERMANN_NOT_FIRST;
//typedef /*S< */S < R< U<1,1>,  U<3, 1>  > ,U<1, 1> > /*, U<3, 1> >*/ ACKERMANN_NOT_FIRST;

typedef S< R < ACKERMANN_FIRST , ACKERMANN_NOT_FIRST >, U<1, 1>, S<NOT ,FIRST_CASE> > ACKERMANN_ITER;

typedef S<PUSH, S <S< PUSH, EMPTY_STACK, U<1, 1> >, U< 2, 1> >, U< 2, 2> > STACK_FROM_PAIR;
typedef R< U<1, 1>, S <ACKERMANN_ITER, U<3, 3> > > N_ACKERMANN_ITERS;

typedef M< S < NOT_READY,  N_ACKERMANN_ITERS > > ITERATIONS;
typedef S< ULT ,  S <S <N_ACKERMANN_ITERS, U<1, 1>, ITERATIONS>, STACK_FROM_PAIR > > ACKERMANN;





int main() {
    cout << sizeof(long double);
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
//    print<STACK_FROM_PAIR>(0, 0);


//    nat stack = N_ACKERMANN_ITERS::apl(STACK_FROM_PAIR::apl(3, 2), 117); // owerflow on 118 iteration




//    print<ITERATIONS>(STACK_FROM_PAIR::apl(3,1));
    print<ACKERMANN>(2, 6);
    return 0;
}

