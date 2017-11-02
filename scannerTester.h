//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_SCANNERTESTER_H
#define FRONTEND_SCANNERTESTER_H

#include "Scanner.h"
#include "token.h"

class Parser{
public:
    Parser(FILE*);
    void parse();

private:
    Scanner scanner;
    struct token currentToken;
    void error(std::string);
    void vars();
    void mvars();
    void program();
    void block();
    void stats();
    void stat();
    void mStat();
    void in();
    void out();
    void check();
    void loop();
    void assign();
    void expr();
    void M();
    void R();
    void F();
    void RO();
};

#endif

//<program>  ->     <vars> <block>
//<block>       ->      Begin <vars> <stats> End
//<vars>          ->      empty | Var Identifier <mvars>
//<mvars>     ->     .  | , Identifier <mvars>
//<expr>        ->      <M> + <expr> | <M> - <expr> | <M>
//<M>              ->     <F> % <M> | <F> * <M> | <F>
//<F>              ->      ( <F> ) | <R>
//<R>              ->      [ <expr> ] | Identifier | Number
//<stats>         ->      <stat>  <mStat>
//<mStat>       ->      empty |  <stat>  <mStat>
//<stat>           ->      <in> | <out> | <block> | <if> | <loop> | <assign>
//<in>              ->      Input Identifier ;
//<out>            ->      Output <expr>  ;
//<if>               ->      Check [ <expr> <RO> <expr> ] <stat>
//<loop>          ->      Loop [ <expr> <RO> <expr> ] <stat>
//<assign>       ->      Identifier : <expr>   ;
//<RO>            ->      < | <= | >  | >= | ==  |  !=