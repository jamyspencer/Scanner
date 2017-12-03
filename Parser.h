//
// Created by jamy on 10/7/17.
//

#ifndef FRONTEND_PARSER_H
#define FRONTEND_PARSER_H

#include "Scanner.h"
#include "token.h"
#include "Node.h"

class Parser{
public:
    Parser(FILE*);
    Node* parse();

private:
    Scanner scanner;
    struct token currentToken;
    void error(std::string);
    Node* vars();
    Node* mvars();
    Node* program();
    Node* block();
    Node* stats();
    Node* stat();
    Node* mStat();
    Node* in();
    Node* out();
    Node* check();
    Node* loop();
    Node* assign();
    Node* expr();
    Node* M();
    Node* R();
    Node* F();
    token RO();
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
//<stat>           ->      <in> | <outFile> | <block> | <if> | <loop> | <assign>
//<in>              ->      Input Identifier ;
//<outFile>            ->      Output <expr>  ;
//<if>               ->      Check [ <expr> <RO> <expr> ] <stat>
//<loop>          ->      Loop [ <expr> <RO> <expr> ] <stat>
//<assign>       ->      Identifier : <expr>   ;
//<RO>            ->      < | <= | >  | >= | ==  |  !=