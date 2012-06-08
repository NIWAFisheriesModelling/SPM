// const char* time_stamp = "$Date: 2008-03-12 11:44:19 +1300 (Wed, 12 Mar 2008) $\n";
// const char* parser_id = "$Id: parser.h 1877 2008-03-11 22:44:19Z fud $\n";

#ifndef PARSER_H
#define PARSER_H

#ifdef WIN32
  
// disable warnings about long names
  #pragma warning( disable : 4786)

#endif
#include <stdexcept>

typedef enum TokenType{
    NONE,
    NAME,
    NUMBER,
    END,
    PLUS='+',
    MINUS='-',
    MULTIPLY='*',
    DIVIDE='/',
    ASSIGN='=',
    LHPAREN='(',
    RHPAREN=')',
    COMMA=',',
    NOT='!',
    
    // comparisons
    LT='<',
    GT='>',
    LE,     // <=
    GE,     // >=
    EQ,     // ==
    NE,     // !=
    AND,    // &&
    OR,      // ||
    
    // special assignments
    
    ASSIGN_ADD,  //  +=
    ASSIGN_SUB,  //  +-
    ASSIGN_MUL,  //  +*
    ASSIGN_DIV   //  +/
    
};    
/*
template <class DOUBLE>
class OneArgFunction{
      typedef DOUBLE (*OneArgFunction_ptr)  (const DOUBLE arg);
      public:
      OneArgFunction_ptr  ptr;
      DOUBLE operator() (const DOUBLE arg) const{
             return ptr(arg);
      }
};

template <class DOUBLE>
class TwoArgFunction{
      typedef DOUBLE (*TwoArgFunction_ptr)  (const DOUBLE arg1, const DOUBLE arg2);
      public:
      TwoArgFunction_ptr  ptr;
      DOUBLE operator() (const DOUBLE arg1, const DOUBLE arg2) const{
             return ptr(arg1,arg2);
      }
};

template <class DOUBLE>
class ThreeArgFunction{
      typedef DOUBLE (*ThreeArgFunction_ptr)  (const DOUBLE arg1, const DOUBLE arg2,const DOUBLE arg3);
      public:
      ThreeArgFunction_ptr  ptr;
      DOUBLE operator() (const DOUBLE arg1, const DOUBLE arg2,const DOUBLE arg3) const{
             return ptr(arg1,arg2,arg3);
      }
};

*/

class OneArgFunction{
      public:
      double (*ptr1) (double arg);
      adub (*ptr2) (const dvariable& arg);

      double operator() (double arg) const {return ptr1(arg);}      
      adub operator() (const dvariable& arg) const {return ptr2(arg);}
};

class TwoArgFunction{
      public:
      double (*ptr1) (double arg1,double arg2);
      adub (*ptr2) (const dvariable& arg1,const dvariable& arg2);

      double operator() (double arg1,double arg2) const {return ptr1(arg1,arg2);}      
      adub operator() (const dvariable& arg1,const dvariable& arg2) const {return ptr2(arg1,arg2);}

};

class ThreeArgFunction{
      public:
      double (*ptr1) (double arg1,double arg2,double arg3);
      dvariable (*ptr2) (const dvariable& arg1,const dvariable& arg2,const dvariable& arg3);

      double operator() (double arg1,double arg2,double arg3) const {return ptr1(arg1,arg2,arg3);}      
      dvariable operator() (const dvariable& arg1,const dvariable& arg2,const dvariable& arg3) const {return ptr2(arg1,arg2,arg3);}
};

template<class DOUBLE>
class Parser
  {
  private:
  std::string program_;
  const char * pWord_;
  const char * pWordStart_;
  // last token parsed
  TokenType type_;
  std::string word_;
  DOUBLE value_;


  public:

  Parser (const std::string & program); 
  
  const DOUBLE Evaluate ();  // get result
  const DOUBLE Evaluate (const std::string & program);  // get result
  const std::vector<std::string> ExportNames();

  // access symbols with operator []
  DOUBLE & operator[] (const std::string & key) { return symbols_ [key]; }

  // symbol table - can be accessed directly (eg. to copy a batch in)
  std::map<std::string, DOUBLE> symbols_;
 
  private:

  const TokenType GetToken (const bool ignoreSign = false);  
  const DOUBLE CommaList (const bool get);
  const DOUBLE Expression (const bool get);
  const DOUBLE Comparison (const bool get);
  const DOUBLE AddSubtract (const bool get);
  const DOUBLE Term (const bool get);      // multiply and divide
  const DOUBLE Primary (const bool get);   // primary (base) tokens

  inline void CheckToken (const TokenType wanted)
    {
    if (type_ != wanted)
      {
      std::ostringstream s;
      s << "'" << static_cast <char> (wanted) << "' expected.";
      throw std::runtime_error (s.str ());    
      }
    }
  };  // end of Parser


#endif // PARSER_H

