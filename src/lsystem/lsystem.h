/**
 * This code is part of libcity library.
 *
 * @file lsystem/lsystem.h
 * @date 05.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for string based L-system rewriting engine.
 *
 * LSystem class is a base for another L-System driven classes.
 * It works with strings to achive maximal complexity of the
 * code (even though it's not optimal).
 *
 * Implementation of this L-System is context-free and deterministic.
 * Stochastic behavior can be achieved as well (@see LSystem::ProductionRule).
 */

#ifndef _LSYSTEM_H_
#define _LSYSTEM_H_

#include <set>
#include <map>
#include <list>
#include <string>

class LSystem
{
  public:
    LSystem();
    virtual ~LSystem();

    /** Production rule of a LSystem.
        With one successor it's a deterministic rule,
        with more successors it's stochastic rule with a
        1/number_of_successors chance of occurence. */
    class ProductionRule
    {
      public:
        ProductionRule();
        ProductionRule(char leftSide, std::string rightSide);

        char predecessor();
        std::string successor();
        void addSuccessor(std::string rightSideString);

      private:
        char leftSide;
        std::list<std::string> rightSide;
    };

    void setIterations(int numberOfIterations);

    void newRule(char predecessor, std::string successor);

    std::string producedString();

  protected:
    std::set<char> alphabet; /**< Finite set of symbols */
    std::string axiom; /**< Initial string */

    /** Production rules are stored in std::map.
        Stochastic rules have more than one successor.
        Which one is used is determined randomly within
        the rule. @see LSystem::ProductionRule */
    std::map<char, ProductionRule> rules;

    int iterations;

    std::list<char> outputString; /**< Produced string */

    std::list<char>::iterator currentPosition;

    void doSingleIteration();
    void rewrite();
    void rewrite(std::list<char>::iterator position);

  private:
    bool isResultReady;
};

#endif
