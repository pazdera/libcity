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

    /**
     * WARNING: will delete producedString!
     */
    void setAxiom(std::string startingSequence);

    /**
     * Does one rewriting iteration on the productionString.
     * NOTICE might return number of rewrites done
     */
    void doNextIteration();

    /**
     * Adds a new rule to the LSystem. All the symbols in
     * the rule must be in the LSystem's alphabet.
     */
    void addRule(char predecessor, std::string successor);

    std::string getProducedString() const; /**< Returns the whole produced string */

  protected:
    /** Internal representation of production rule of a LSystem.
        With one successor it's a deterministic rule,
        with more successors it's stochastic rule with a
        1/number_of_successors chance of occurence. */
    class ProductionRule
    {
      public:
        ProductionRule();
        ProductionRule(char leftSide, std::string rightSide);

        char predecessor() const;
        std::string successor() const;
        void addSuccessor(std::string rightSideString);

      private:
        char leftSide;
        std::list<std::string> rightSide;
    };

    /** 
     * Internal representation of a symbol in a
     * LSystem. It's just a single character, but
     * extended to store various parameters.
     */
    class Symbol
    {
      public:
        Symbol(char character);
        virtual ~Symbol();

        void markAsRead();

        bool isMarkedRead() const;
        char getSymbol() const;

        operator char() const;
        bool operator==(char character) const;
        bool operator==(Symbol another) const;

      protected:
        char symbol;
        bool alreadyRead;
    };

    std::set<char> alphabet; /**< Finite set of symbols */
    std::string axiom; /**< Initial string */

    /** Production rules are stored in std::map.
        Stochastic rules have more than one successor.
        Which one is used is determined randomly within
        the rule. @see LSystem::ProductionRule */
    std::map<char, ProductionRule> rules;

    std::list<Symbol> producedString; /**< Produced string */

    /** 
     * Attempts to rewrite character specified by
     * the position iterator. */
    void rewrite(std::list<Symbol>::iterator position);

  private:
    bool isInAlphabet(char checkedCharacter) const; /**< Check if character is in this LSystem's alphabet */
    bool isInAlphabet(std::string checkedString) const; /**< Checks the whole string */
};

#endif
