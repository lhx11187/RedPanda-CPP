/*
 * Copyright (C) 2020-2022 Roy Qu (royqh1979@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "cpp.h"
#include "../Constants.h"

#include <QFont>

namespace QSynedit {

static const QSet<QString> CppStatementKeyWords {
    "if",
    "for",
    "try",
    "catch",
    "else",
    "while",
    "do"
};



const QSet<QString> CppHighlighter::Keywords {
    "and",
    "and_eq",
    "bitand",
    "bitor",
    "break",
    "compl",
    "constexpr",
    "const_cast",
    "continue",
    "dynamic_cast",
    "else",
    "explicit",
    "export",
    "extern",
    "false",
    "for",
    "mutable",
    "noexcept",
    "not",
    "not_eq",
    "nullptr",
    "or",
    "or_eq",
    "register",
    "reinterpret_cast",
    "static_assert",
    "static_cast",
    "template",
    "this",
    "thread_local",
    "true",
    "typename",
    "virtual",
    "volatile",
    "xor",
    "xor_eq",
    "delete",
    "delete[]",
    "goto",
    "new",
    "return",
    "throw",
    "using",
    "case",
    "default",

    "alignas",
    "alignof",
    "decltype",
    "if",
    "sizeof",
    "switch",
    "typeid",
    "while",

    "asm",
    "catch",
    "do",
    "namespace",
    "try",

    "atomic_cancel",
    "atomic_commit",
    "atomic_noexcept",
    "concept",
    "consteval",
    "constinit",
    "co_wait",
    "co_return",
    "co_yield",
    "reflexpr",
    "requires",

    "auto",
    "bool",
    "char",
    "char8_t",
    "char16_t",
    "char32_t",
    "double",
    "float",
    "int",
    "long",
    "short",
    "signed",
    "unsigned",
    "void",
    "wchar_t",

    "const",
    "inline",

    "class",
    "enum",
    "friend",
    "operator",
    "private",
    "protected",
    "public",
    "static",
    "struct",
    "typedef",
    "union",

    "nullptr",
};
CppHighlighter::CppHighlighter(): Highlighter()
{
    mAsmAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrAssembler);
    addAttribute(mAsmAttribute);
    mCharAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrCharacter);
    addAttribute(mCharAttribute);
    mCommentAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrComment);
    addAttribute(mCommentAttribute);
    mClassAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrClass);
    addAttribute(mClassAttribute);
    mFloatAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrFloat);
    addAttribute(mFloatAttribute);
    mFunctionAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrFunction);
    addAttribute(mFunctionAttribute);
    mGlobalVarAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrGlobalVariable);
    addAttribute(mGlobalVarAttribute);
    mHexAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrHexadecimal);
    addAttribute(mHexAttribute);
    mIdentifierAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrIdentifier);
    addAttribute(mIdentifierAttribute);
    mInvalidAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrIllegalChar);
    addAttribute(mInvalidAttribute);
    mLocalVarAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrLocalVariable);
    addAttribute(mLocalVarAttribute);
    mNumberAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrNumber);
    addAttribute(mNumberAttribute);
    mOctAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrOctal);
    addAttribute(mOctAttribute);
    mPreprocessorAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrPreprocessor);
    addAttribute(mPreprocessorAttribute);
    mKeywordAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrReservedWord);
    addAttribute(mKeywordAttribute);
    mWhitespaceAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrSpace);
    addAttribute(mWhitespaceAttribute);
    mStringAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrString);
    addAttribute(mStringAttribute);
    mStringEscapeSequenceAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrStringEscapeSequences);
    addAttribute(mStringEscapeSequenceAttribute);
    mSymbolAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrSymbol);
    addAttribute(mSymbolAttribute);
    mVariableAttribute = std::make_shared<HighlighterAttribute>(SYNS_AttrVariable);
    addAttribute(mVariableAttribute);

    resetState();
}

PHighlighterAttribute CppHighlighter::asmAttribute() const
{
    return mAsmAttribute;
}

PHighlighterAttribute CppHighlighter::preprocessorAttribute() const
{
    return mPreprocessorAttribute;
}

PHighlighterAttribute CppHighlighter::invalidAttribute() const
{
    return mInvalidAttribute;
}

PHighlighterAttribute CppHighlighter::numberAttribute() const
{
    return mNumberAttribute;
}

PHighlighterAttribute CppHighlighter::floatAttribute() const
{
    return mFloatAttribute;
}

PHighlighterAttribute CppHighlighter::hexAttribute() const
{
    return mHexAttribute;
}

PHighlighterAttribute CppHighlighter::octAttribute() const
{
    return mOctAttribute;
}

PHighlighterAttribute CppHighlighter::stringEscapeSequenceAttribute() const
{
    return mStringEscapeSequenceAttribute;
}

PHighlighterAttribute CppHighlighter::charAttribute() const
{
    return mCharAttribute;
}

PHighlighterAttribute CppHighlighter::variableAttribute() const
{
    return mVariableAttribute;
}

PHighlighterAttribute CppHighlighter::functionAttribute() const
{
    return mFunctionAttribute;
}

PHighlighterAttribute CppHighlighter::classAttribute() const
{
    return mClassAttribute;
}

PHighlighterAttribute CppHighlighter::globalVarAttribute() const
{
    return mGlobalVarAttribute;
}

PHighlighterAttribute CppHighlighter::localVarAttribute() const
{
    return mLocalVarAttribute;
}

CppHighlighter::ExtTokenId CppHighlighter::getExtTokenId()
{
    return mExtTokenId;
}

TokenKind CppHighlighter::getTokenId()
{
    if ((mRange.state == RangeState::rsAsm || mRange.state == RangeState::rsAsmBlock)
            && !mAsmStart && !(mTokenId == TokenId::Comment || mTokenId == TokenId::Space
                               || mTokenId == TokenId::Null)) {
        return TokenId::Asm;
    } else {
        return mTokenId;
    }
}

void CppHighlighter::andSymbolProc()
{
    mTokenId = TokenId::Symbol;
    switch (mLine[mRun+1].unicode()) {
    case '=':
        mRun+=2;
        mExtTokenId = ExtTokenId::AndAssign;
        break;
    case '&':
        mRun+=2;
        mExtTokenId = ExtTokenId::LogAnd;
        break;
    default:
        mRun+=1;
        mExtTokenId = ExtTokenId::And;
    }
}

void CppHighlighter::ansiCppProc()
{
    mTokenId = TokenId::Comment;
    if (mLine[mRun]==0) {
        nullProc();
        if  ( (mRun<1)  || (mLine[mRun-1]!='\\')) {
            mRange.state = RangeState::rsUnknown;
            return;
        }
    }
    while (mLine[mRun]!=0) {
        mRun+=1;
    }
    mRange.state = RangeState::rsCppCommentEnded;
    if (mLine[mRun-1] == '\\' && mLine[mRun]==0) { // continues on next line
        mRange.state = RangeState::rsCppComment;
    }
}

void CppHighlighter::ansiCProc()
{
    bool finishProcess = false;
    mTokenId = TokenId::Comment;
    if (mLine[mRun].unicode() == 0) {
        nullProc();
        return;
    }
    while (mLine[mRun]!=0) {
        switch(mLine[mRun].unicode()) {
        case '*':
            if (mLine[mRun+1] == '/') {
                mRun += 2;
                if (mRange.state == RangeState::rsAnsiCAsm) {
                    mRange.state = RangeState::rsAsm;
                } else if (mRange.state == RangeState::rsAnsiCAsmBlock){
                    mRange.state = RangeState::rsAsmBlock;
                } else if (mRange.state == RangeState::rsDirectiveComment &&
                           mLine[mRun] != 0 && mLine[mRun]!='\r' && mLine[mRun]!='\n') {
                    mRange.state = RangeState::rsMultiLineDirective;
                } else {
                    mRange.state = RangeState::rsUnknown;
                }
                finishProcess = true;
            } else
                mRun+=1;
            break;
        default:
            mRun+=1;
        }
        if (finishProcess)
            break;
    }
}

void CppHighlighter::asciiCharProc()
{
    mTokenId = TokenId::Char;
    do {
        if (mLine[mRun] == '\\') {
            if (mLine[mRun+1] == '\'' || mLine[mRun+1] == '\\') {
                mRun+=1;
            }
        }
        mRun+=1;
    } while (mLine[mRun]!=0 && mLine[mRun]!='\'');
    if (mLine[mRun] == '\'')
        mRun+=1;
    mRange.state = RangeState::rsUnknown;
}

void CppHighlighter::atSymbolProc()
{
    mTokenId = TokenId::Unknown;
    mRun+=1;
}

void CppHighlighter::braceCloseProc()
{
    mRun += 1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::BraceClose;
    if (mRange.state == RangeState::rsAsmBlock) {
        mRange.state = rsUnknown;
    }

    mRange.braceLevel -= 1;
    if (mRange.braceLevel<0)
        mRange.braceLevel = 0;
    if (mRange.leftBraces>0) {
        mRange.leftBraces--;
    } else {
        mRange.rightBraces++ ;
    }
    popIndents(sitBrace);
}

void CppHighlighter::braceOpenProc()
{
    mRun += 1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::BraceOpen;
    if (mRange.state == RangeState::rsAsm) {
        mRange.state = RangeState::rsAsmBlock;
        mAsmStart = true;
    }
    mRange.braceLevel += 1;
    mRange.leftBraces++;
    if (mRange.getLastIndent() == sitStatement) {
        // if last indent is started by 'if' 'for' etc
        // just replace it
        while (mRange.getLastIndent() == sitStatement)
            popIndents(sitStatement);
        pushIndents(sitBrace);
//        int idx = mRange.indents.length()-1;
//        if (idx < mRange.firstIndentThisLine) {
//            mRange.firstIndentThisLine = idx;
//        }
//        mRange.indents.replace(idx,1,BraceIndentType);
    } else {
        pushIndents(sitBrace);
    }
}

void CppHighlighter::colonProc()
{
    mTokenId = TokenId::Symbol;
    if (mLine[mRun+1]==':') {
        mRun+=2;
        mExtTokenId = ExtTokenId::ScopeResolution;
    } else {
        mRun+=1;
        mExtTokenId = ExtTokenId::Colon;
    }
}

void CppHighlighter::commaProc()
{
    mRun+=1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::Comma;
}

void CppHighlighter::directiveProc()
{
    QString preContents = mLineString.left(mRun).trimmed();
    if (!preContents.isEmpty()) { // '#' is not first non-space char on the line, treat it as an invalid char
       mTokenId = TokenId::Unknown;
       mRun+=1;
       return;
    }
    mTokenId = TokenId::Directive;
    mRun+=1;
    //skip spaces
    while (mLine[mRun]!=0 && isSpaceChar(mLine[mRun])) {
        mRun+=1;
    }

    QString directive;
    while (mLine[mRun]!=0 && isIdentChar(mLine[mRun])) {
        directive+=mLine[mRun];
        mRun+=1;
    }
    if (directive == "define") {
        while(mLine[mRun]!=0 && isSpaceChar(mLine[mRun]))
            mRun++;
        mRange.state = RangeState::rsDefineIdentifier;
        return;
    } else
        mRange.state = RangeState::rsUnknown;
}

void CppHighlighter::defineIdentProc()
{
    mTokenId = TokenId::Identifier;
    while(mLine[mRun]!=0 && isIdentChar(mLine[mRun]))
        mRun++;
    mRange.state = RangeState::rsDefineRemaining;
}

void CppHighlighter::defineRemainingProc()
{
    mTokenId = TokenId::Directive;
    do {
        switch(mLine[mRun].unicode()) {
        case '/': //comment?
            switch (mLine[mRun+1].unicode()) {
            case '/': // is end of directive as well
                mRange.state = RangeState::rsUnknown;
                return;
            case '*': // might be embeded only
                mRange.state = RangeState::rsDirectiveComment;
                return;
            }
            break;
        case '\\': // yet another line?
            if (mLine[mRun+1] == 0) {
                mRun+=1;
                mRange.state = RangeState::rsMultiLineDirective;
                return;
            }
            break;
        }
        mRun+=1;
    } while (mLine[mRun]!=0);
    mRange.state=RangeState::rsUnknown;
}

void CppHighlighter::directiveEndProc()
{
    mTokenId = TokenId::Directive;
    if (mLine[mRun] == 0) {
        nullProc();
        return;
    }
    mRange.state = RangeState::rsUnknown;
    do {
        switch(mLine[mRun].unicode()) {
        case '/': //comment?
            switch (mLine[mRun+1].unicode()) {
            case '/': // is end of directive as well
                mRange.state = RangeState::rsUnknown;
                return;
            case '*': // might be embeded only
                mRange.state = RangeState::rsDirectiveComment;
                return;
            }
            break;
        case '\\': // yet another line?
              if (mLine[mRun+1] == 0) {
                  mRun+=1;
                  mRange.state = RangeState::rsMultiLineDirective;
                  return;
            }
            break;
        }
        mRun+=1;
    } while (mLine[mRun]!=0);
}

void CppHighlighter::equalProc()
{
    mTokenId = TokenId::Symbol;
    if (mLine[mRun+1] == '=') {
        mRun += 2;
        mExtTokenId = ExtTokenId::LogEqual;
    } else {
        mRun += 1;
        mExtTokenId = ExtTokenId::Assign;
    }
}

void CppHighlighter::greaterProc()
{
    mTokenId = TokenId::Symbol;
    switch (mLine[mRun + 1].unicode()) {
    case '=':
        mRun += 2;
        mExtTokenId = ExtTokenId::GreaterThanEqual;
        break;
    case '>':
        if (mLine[mRun+2] == '=') {
            mRun+=3;
            mExtTokenId = ExtTokenId::ShiftRightAssign;
        } else {
            mRun += 2;
            mExtTokenId = ExtTokenId::ShiftRight;
        }
        break;
    default:
        mRun+=1;
        mExtTokenId = ExtTokenId::GreaterThan;
    }
}

void CppHighlighter::identProc()
{
    int wordEnd = mRun;
    while (isIdentChar(mLine[wordEnd])) {
        wordEnd+=1;
    }
    QString word = mLineString.mid(mRun,wordEnd-mRun);
    mRun=wordEnd;
    if (isKeyword(word)) {
        mTokenId = TokenId::Key;
        if (CppStatementKeyWords.contains(word)) {
            pushIndents(sitStatement);
        }
    } else {
        mTokenId = TokenId::Identifier;
    }
}

void CppHighlighter::lowerProc()
{
    mTokenId = TokenId::Symbol;
    switch(mLine[mRun+1].unicode()) {
    case '=':
        mRun+=2;
        mExtTokenId = ExtTokenId::LessThanEqual;
        break;
    case '<':
        if (mLine[mRun+2] == '=') {
            mRun+=3;
            mExtTokenId = ExtTokenId::ShiftLeftAssign;
        } else {
            mRun+=2;
            mExtTokenId = ExtTokenId::ShiftLeft;
        }
        break;
    default:
        mRun+=1;
        mExtTokenId = ExtTokenId::LessThan;
    }
}

void CppHighlighter::minusProc()
{
    mTokenId = TokenId::Symbol;
    switch(mLine[mRun+1].unicode()) {
    case '=':
        mRun += 2;
        mExtTokenId = ExtTokenId::SubtractAssign;
        break;
    case '-':
        mRun += 2;
        mExtTokenId = ExtTokenId::Decrement;
        break;
    case '>':
        if (mLine[mRun+2]=='*') {
            mRun += 3;
            mExtTokenId = ExtTokenId::PointerToMemberOfPointer;
        } else {
            mRun += 2;
            mExtTokenId = ExtTokenId::Arrow;
        }
        break;
    default:
        mRun += 1;
        mExtTokenId = ExtTokenId::Subtract;
    }
}

void CppHighlighter::modSymbolProc()
{
    mTokenId = TokenId::Symbol;
    switch(mLine[mRun + 1].unicode()) {
    case '=':
        mRun += 2;
        mExtTokenId = ExtTokenId::ModAssign;
        break;
    default:
        mRun += 1;
        mExtTokenId = ExtTokenId::Mod;
    }
}

void CppHighlighter::notSymbolProc()
{
    mTokenId = TokenId::Symbol;
    switch(mLine[mRun + 1].unicode()) {
    case '=':
        mRun+=2;
        mExtTokenId = ExtTokenId::NotEqual;
        break;
    default:
        mRun+=1;
        mExtTokenId = ExtTokenId::LogComplement;
    }
}

void CppHighlighter::nullProc()
{
    if ((mRun-1>=0) && isSpaceChar(mLine[mRun-1]) &&
    (mRange.state == RangeState::rsCppComment
     || mRange.state == RangeState::rsDirective
     || mRange.state == RangeState::rsString
     || mRange.state == RangeState::rsMultiLineString
     || mRange.state == RangeState::rsMultiLineDirective) ) {
        mRange.state = RangeState::rsUnknown;
    } else
        mTokenId = TokenId::Null;
}

void CppHighlighter::numberProc()
{
    int idx1; // token[1]
    idx1 = mRun;
    mRun+=1;
    mTokenId = TokenId::Number;
    bool shouldExit = false;
    while (mLine[mRun]!=0) {
        switch(mLine[mRun].unicode()) {
        case '\'':
            if (mTokenId != TokenId::Number) {
                mTokenId = TokenId::Symbol;
                return;
            }
            break;
        case '.':
            if (mLine[mRun+1] == '.') {
                mRun+=2;
                mTokenId = TokenId::Unknown;
                return;
            } else if (mTokenId != TokenId::Hex) {
                mTokenId = TokenId::Float;
            } else {
                mTokenId = TokenId::Unknown;
                return;
            }
            break;
        case '-':
        case '+':
            if (mTokenId != TokenId::Float) // number <> float. an arithmetic operator
                return;
            if (mLine[mRun-1]!= 'e' && mLine[mRun-1]!='E')  // number = float, but no exponent. an arithmetic operator
                return;
            if (mLine[mRun+1]<'0' || mLine[mRun+1]>'9')  {// invalid
                mRun+=1;
                mTokenId = TokenId::Unknown;
                return;
            }
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
            if ((mRun == idx1+1) && (mLine[idx1] == '0')) { // octal number
                mTokenId = TokenId::Octal;
            }
            break;
        case '8':
        case '9':
            if ( (mLine[idx1]=='0') && (mTokenId != TokenId::Hex)  && (mTokenId != TokenId::Float) ) // invalid octal char
                mTokenId = TokenId::Unknown; // we must continue parse, it may be an float number
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            if (mTokenId!=TokenId::Hex) { //invalid
                mTokenId = TokenId::Unknown;
                return;
            }
            break;
        case 'e':
        case 'E':
            if (mTokenId!=TokenId::Hex) {
                if (mLine[mRun-1]>='0' || mLine[mRun-1]<='9' ) {//exponent
                    for (int i=idx1;i<mRun;i++) {
                        if (mLine[i] == 'e' || mLine[i]=='E') { // too many exponents
                            mRun+=1;
                            mTokenId = TokenId::Unknown;
                            return;
                        }
                    }
                    if (mLine[mRun+1]!='+' && mLine[mRun+1]!='-' && !(mLine[mRun+1]>='0' && mLine[mRun+1]<='9')) {
                        return;
                    } else {
                        mTokenId = TokenId::Float;
                    }
                } else {
                    mRun+=1;
                    mTokenId = TokenId::Unknown;
                    return;
                }
            }
            break;
        case 'f':
        case 'F':
            if (mTokenId!=TokenId::Hex) {
                for (int i=idx1;i<mRun;i++) {
                    if (mLine[i] == 'f' || mLine[i]=='F') {
                        mRun+=1;
                        mTokenId = TokenId::Unknown;
                        return;
                    }
                }
                if (mTokenId == TokenId::Float) {
                    if (mLine[mRun-1]=='l' || mLine[mRun-1]=='L') {
                        mRun+=1;
                        mTokenId = TokenId::Unknown;
                        return;
                    }
                } else {
                    mTokenId = TokenId::Float;
                }
            }
            break;
        case 'l':
        case 'L':
            for (int i=idx1;i<=mRun-2;i++) {
                if (mLine[i] == 'l' && mLine[i]=='L') {
                    mRun+=1;
                    mTokenId = TokenId::Unknown;
                    return;
                }
            }
            if (mTokenId == TokenId::Float && (mLine[mRun-1]=='f' || mLine[mRun-1]=='F')) {
                mRun+=1;
                mTokenId = TokenId::Unknown;
                return;
            }
            break;
        case 'u':
        case 'U':
            if (mTokenId == TokenId::Float) {
                mRun+=1;
                mTokenId = TokenId::Unknown;
                return;
            } else {
                for (int i=idx1;i<mRun;i++) {
                    if (mLine[i] == 'u' || mLine[i]=='U') {
                        mRun+=1;
                        mTokenId = TokenId::Unknown;
                        return;
                    }
                }
            }
            break;
        case 'x':
        case 'X':
            if ((mRun == idx1+1) && (mLine[idx1]=='0') &&
                    ((mLine[mRun+1]>='0' && mLine[mRun+1]<='9')
                     || (mLine[mRun+1]>='a' && mLine[mRun+1]<='f')
                     || (mLine[mRun+1]>='A' && mLine[mRun+1]<='F')) ) {
                mTokenId = TokenId::Hex;
            } else {
                mRun+=1;
                mTokenId = TokenId::Unknown;
                return;
            }
            break;
        default:
            shouldExit=true;
        }
        if (shouldExit) {
            break;
        }
        mRun+=1;        
    }
    if (mLine[mRun-1] == '\'') {
        mTokenId = TokenId::Unknown;
    }
}

void CppHighlighter::orSymbolProc()
{
    mTokenId = TokenId::Symbol;
    switch ( mLine[mRun+1].unicode()) {
    case '=':
        mRun+=2;
        mExtTokenId = ExtTokenId::IncOrAssign;
        break;
    case '|':
        mRun+=2;
        mExtTokenId = ExtTokenId::LogOr;
        break;
    default:
        mRun+=1;
        mExtTokenId = ExtTokenId::IncOr;
    }
}

void CppHighlighter::plusProc()
{
    mTokenId = TokenId::Symbol;
    switch(mLine[mRun+1].unicode()){
    case '=':
        mRun+=2;
        mExtTokenId = ExtTokenId::AddAssign;
        break;
    case '+':
        mRun+=2;
        mExtTokenId = ExtTokenId::Increment;
        break;
    default:
        mRun+=1;
        mExtTokenId = ExtTokenId::Add;
    }
}

void CppHighlighter::pointProc()
{
    mTokenId = TokenId::Symbol;
    if (mLine[mRun+1] == '*' ) {
        mRun+=2;
        mExtTokenId = ExtTokenId::PointerToMemberOfObject;
    } else if (mLine[mRun+1] == '.' && mLine[mRun+2] == '.') {
        mRun+=3;
        mExtTokenId = ExtTokenId::Ellipse;
    } else if (mLine[mRun+1]>='0' && mLine[mRun+1]<='9') {
        numberProc();
    } else {
        mRun+=1;
        mExtTokenId = ExtTokenId::Point;
    }
}

void CppHighlighter::questionProc()
{
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::Question;
    mRun+=1;
}

void CppHighlighter::rawStringProc()
{
    bool noEscaping = false;
    if (mRange.state == RangeState::rsRawStringNotEscaping)
        noEscaping = true;
    mTokenId = TokenId::RawString;
    mRange.state = RangeState::rsRawString;

    while (mLine[mRun]!=0) {
        if ((!noEscaping) && (mLine[mRun]=='"')) {
            mRun+=1;
            break;
        }
        switch (mLine[mRun].unicode()) {
        case '(':
            noEscaping = true;
            break;
        case ')':
            noEscaping = false;
            break;
        }
        mRun+=1;
    }
    mRange.state = RangeState::rsUnknown;
}

void CppHighlighter::roundCloseProc()
{
    mRun += 1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::RoundClose;
    mRange.parenthesisLevel--;
    if (mRange.parenthesisLevel<0)
        mRange.parenthesisLevel=0;
    popIndents(sitParenthesis);
}

void CppHighlighter::roundOpenProc()
{
    mRun += 1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::RoundOpen;
    mRange.parenthesisLevel++;
    pushIndents(sitParenthesis);
}

void CppHighlighter::semiColonProc()
{
    mRun += 1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::SemiColon;
    if (mRange.state == RangeState::rsAsm)
        mRange.state = RangeState::rsUnknown;
    while (mRange.getLastIndent() == sitStatement) {
        popIndents(sitStatement);
    }
}

void CppHighlighter::slashProc()
{
    switch(mLine[mRun+1].unicode()) {
    case '/': // Cpp style comment
        mTokenId = TokenId::Comment;
        mRun+=2;
        mRange.state = RangeState::rsCppComment;
        return;
    case '*': // C style comment
        mTokenId = TokenId::Comment;
        if (mRange.state == RangeState::rsAsm) {
            mRange.state = RangeState::rsAnsiCAsm;
        } else if (mRange.state == RangeState::rsAsmBlock) {
            mRange.state = RangeState::rsAnsiCAsmBlock;
        } else if (mRange.state == RangeState::rsDirective) {
            mRange.state = RangeState::rsDirectiveComment;
        } else {
            mRange.state = RangeState::rsAnsiC;
        }
        mRun += 2;
        if (mLine[mRun]!=0)
            ansiCProc();
        break;
    case '=':
        mRun+=2;
        mTokenId = TokenId::Symbol;
        mExtTokenId = ExtTokenId::DivideAssign;
        break;
    default:
        mRun += 1;
        mTokenId = TokenId::Symbol;
        mExtTokenId = ExtTokenId::Divide;
    }
}

void CppHighlighter::backSlashProc()
{
    if (mLine[mRun+1]==0) {
        mTokenId = TokenId::Symbol;
        mExtTokenId = ExtTokenId::BackSlash;
    } else {
        mTokenId = TokenId::Unknown;
    }
    mRun+=1;
}

void CppHighlighter::spaceProc()
{
    mRun += 1;
    mTokenId = TokenId::Space;
    while (mLine[mRun]>=1 && mLine[mRun]<=32)
        mRun+=1;
    mRange.state = RangeState::rsUnknown;
}

void CppHighlighter::squareCloseProc()
{
    mRun+=1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::SquareClose;
    mRange.bracketLevel--;
    if (mRange.bracketLevel<0)
        mRange.bracketLevel=0;
    popIndents(sitBracket);
}

void CppHighlighter::squareOpenProc()
{
    mRun+=1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::SquareOpen;
    mRange.bracketLevel++;
    pushIndents(sitBracket);
}

void CppHighlighter::starProc()
{
    mTokenId = TokenId::Symbol;
    if (mLine[mRun+1] == '=') {
        mRun += 2;
        mExtTokenId = ExtTokenId::MultiplyAssign;
    } else {
        mRun += 1;
        mExtTokenId = ExtTokenId::Star;
    }
}

void CppHighlighter::stringEndProc()
{
    mTokenId = TokenId::String;
    if (mLine[mRun]==0) {
        nullProc();
        return;
    }
    mRange.state = RangeState::rsUnknown;

    while (mLine[mRun]!=0) {
        if (mLine[mRun]=='"') {
            mRun += 1;
            break;
        }
        if (mLine[mRun].unicode()=='\\') {
            switch(mLine[mRun+1].unicode()) {
            case '\'':
            case '"':
            case '\\':
            case '?':
            case 'a':
            case 'b':
            case 'f':
            case 'n':
            case 'r':
            case 't':
            case 'v':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'x':
            case 'u':
            case 'U':
                mRange.state = RangeState::rsMultiLineStringEscapeSeq;
                return;
            case 0:
                mRun+=1;
                mRange.state = RangeState::rsMultiLineString;
                return;
            }
        }
        mRun += 1;
    }
}

void CppHighlighter::stringEscapeSeqProc()
{
    mTokenId = TokenId::StringEscapeSeq;
    mRun+=1;
    switch(mLine[mRun].unicode()) {
    case '\'':
    case '"':
    case '?':
    case 'a':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
    case 'v':
    case '\\':
        mRun+=1;
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
        for (int i=0;i<3;i++) {
            if (mLine[mRun]<'0' || mLine[mRun]>'7')
                break;
            mRun+=1;
        }
        break;
    case '8':
    case '9':
        mTokenId = TokenId::Unknown;
        mRun+=1;
        break;
    case 'x':
        mRun+=1;
        if ( !(
                 (mLine[mRun]>='0' && mLine[mRun]<='9')
               ||  (mLine[mRun]>='a' && mLine[mRun]<='f')
               ||  (mLine[mRun]>='A' && mLine[mRun]<='F')
                )) {
            mTokenId = TokenId::Unknown;
        } else {
            while (
                   (mLine[mRun]>='0' && mLine[mRun]<='9')
                 ||  (mLine[mRun]>='a' && mLine[mRun]<='f')
                 ||  (mLine[mRun]>='A' && mLine[mRun]<='F')
                   )  {
                mRun+=1;
            }
        }
        break;
    case 'u':
        mRun+=1;
        for (int i=0;i<4;i++) {
            if (mLine[mRun]<'0' || mLine[mRun]>'7') {
                mTokenId = TokenId::Unknown;
                return;
            }
            mRun+=1;
        }
        break;
    case 'U':
        mRun+=1;
        for (int i=0;i<8;i++) {
            if (mLine[mRun]<'0' || mLine[mRun]>'7') {
                mTokenId = TokenId::Unknown;
                return;
            }
            mRun+=1;
        }
        break;
    }
    if (mRange.state == RangeState::rsMultiLineStringEscapeSeq)
        mRange.state = RangeState::rsMultiLineString;
    else
        mRange.state = RangeState::rsString;
}

void CppHighlighter::stringProc()
{
    if (mLine[mRun] == 0) {
        mRange.state = RangeState::rsUnknown;
        return;
    }
    mTokenId = TokenId::String;
    mRange.state = RangeState::rsString;
    while (mLine[mRun]!=0) {
        if (mLine[mRun]=='"') {
            mRun+=1;
            break;
        }
        if (mLine[mRun].unicode()=='\\') {
            switch(mLine[mRun+1].unicode()) {
            case '\'':
            case '"':
            case '\\':
            case '?':
            case 'a':
            case 'b':
            case 'f':
            case 'n':
            case 'r':
            case 't':
            case 'v':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'x':
            case 'u':
            case 'U':
                mRange.state = RangeState::rsStringEscapeSeq;
                return;
            case 0:
                mRun+=1;
                mRange.state = RangeState::rsMultiLineString;
                return;
            }
        }
        mRun+=1;
    }
    mRange.state = RangeState::rsUnknown;
}

void CppHighlighter::stringStartProc()
{
    mTokenId = TokenId::String;
    mRun += 1;
    if (mLine[mRun]==0) {
        mRange.state = RangeState::rsUnknown;
        return;
    }
    stringProc();
}

void CppHighlighter::tildeProc()
{
    mRun+=1;
    mTokenId = TokenId::Symbol;
    mExtTokenId = ExtTokenId::BitComplement;
}

void CppHighlighter::unknownProc()
{
    mRun+=1;
    mTokenId = TokenId::Unknown;
}

void CppHighlighter::xorSymbolProc()
{
    mTokenId = TokenId::Symbol;
    if (mLine[mRun+1]=='=') {
        mRun+=2;
        mExtTokenId = ExtTokenId::XorAssign;
    } else {
        mRun+=1;
        mExtTokenId = ExtTokenId::Xor;
    }
}

void CppHighlighter::processChar()
{
    switch(mLine[mRun].unicode()) {
    case '&':
        andSymbolProc();
        break;
    case '\'':
        asciiCharProc();
        break;
    case '@':
        atSymbolProc();
        break;
    case '}':
        braceCloseProc();
        break;
    case '{':
        braceOpenProc();
        break;
    case '\r':
    case '\n':
        spaceProc();
        break;
    case ':':
        colonProc();
        break;
    case ',':
        commaProc();
        break;
    case '#':
        directiveProc();
        break;
    case '=':
        equalProc();
        break;
    case '>':
        greaterProc();
        break;
    case '?':
        questionProc();
        break;
    case '<':
        lowerProc();
        break;
    case '-':
        minusProc();
        break;
    case '%':
        modSymbolProc();
        break;
    case '!':
        notSymbolProc();
        break;
    case '\\':
        backSlashProc();
        break;
    case 0:
        nullProc();
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        numberProc();
        break;
    case '|':
        orSymbolProc();
        break;
    case '+':
        plusProc();
        break;
    case '.':
        pointProc();
        break;
    case ')':
        roundCloseProc();
        break;
    case '(':
        roundOpenProc();
        break;
    case ';':
        semiColonProc();
        break;
    case '/':
        slashProc();
        break;
    case ']':
        squareCloseProc();
        break;
    case '[':
        squareOpenProc();
        break;
    case '*':
        starProc();
        break;
    case '"':
        stringStartProc();
        break;
    case '~':
        tildeProc();
        break;
    case '^':
        xorSymbolProc();
        break;
    default:
        if (isIdentChar(mLine[mRun])) {
            identProc();
        } else if (isSpaceChar(mLine[mRun])) {
            spaceProc();
        } else {
            unknownProc();
        }
    }
}

void CppHighlighter::popIndents(int indentType)
{
    while (!mRange.indents.isEmpty() && mRange.indents.back()!=indentType) {
        mRange.indents.pop_back();
    }
    if (!mRange.indents.isEmpty()) {
        int idx = mRange.indents.length()-1;
        if (idx < mRange.firstIndentThisLine) {
            mRange.matchingIndents.append(mRange.indents[idx]);
        }
        mRange.indents.pop_back();
    }
}

void CppHighlighter::pushIndents(int indentType)
{
    int idx = mRange.indents.length();
    if (idx<mRange.firstIndentThisLine)
        mRange.firstIndentThisLine = idx;
    mRange.indents.push_back(indentType);
}

bool CppHighlighter::getTokenFinished() const
{
    if (mTokenId == TokenId::Comment
            || mTokenId == TokenId::String
            || mTokenId == TokenId::RawString) {
        return mRange.state == RangeState::rsUnknown;
    }
    return true;
}

bool CppHighlighter::isLastLineCommentNotFinished(int state) const
{
    return (state == RangeState::rsAnsiC ||
            state == RangeState::rsAnsiCAsm ||
            state == RangeState::rsAnsiCAsmBlock ||
            state == RangeState::rsDirectiveComment||
            state == RangeState::rsCppComment);
}

bool CppHighlighter::isLastLineStringNotFinished(int state) const
{
    return state == RangeState::rsMultiLineString;
}

bool CppHighlighter::eol() const
{
    return mTokenId == TokenId::Null;
}

QString CppHighlighter::getToken() const
{
    return mLineString.mid(mTokenPos,mRun-mTokenPos);
}

PHighlighterAttribute CppHighlighter::getTokenAttribute() const
{
    switch (mTokenId) {
    case TokenId::Asm:
        return mAsmAttribute;
    case TokenId::Comment:
        return mCommentAttribute;
    case TokenId::Directive:
        return mPreprocessorAttribute;
    case TokenId::Identifier:
        return mIdentifierAttribute;
    case TokenId::Key:
        return mKeywordAttribute;
    case TokenId::Number:
        return mNumberAttribute;
    case TokenId::Float:
    case TokenId::HexFloat:
        return mFloatAttribute;
    case TokenId::Hex:
        return mHexAttribute;
    case TokenId::Octal:
        return mOctAttribute;
    case TokenId::Space:
        return mWhitespaceAttribute;
    case TokenId::String:
        return mStringAttribute;
    case TokenId::StringEscapeSeq:
        return mStringEscapeSequenceAttribute;
    case TokenId::RawString:
        return mStringAttribute;
    case TokenId::Char:
        return mCharAttribute;
    case TokenId::Symbol:
        return mSymbolAttribute;
    case TokenId::Unknown:
        return mInvalidAttribute;
    default:
        return mInvalidAttribute;
    }
}

TokenKind CppHighlighter::getTokenKind()
{
    return mTokenId;
}

int CppHighlighter::getTokenPos()
{
    return mTokenPos;
}

void CppHighlighter::next()
{
    mAsmStart = false;
    mTokenPos = mRun;
    do {
        switch (mRange.state) {
        case RangeState::rsAnsiC:
        case RangeState::rsAnsiCAsm:
        case RangeState::rsAnsiCAsmBlock:
        case RangeState::rsDirectiveComment:
            ansiCProc();
            break;
        case RangeState::rsString:
            stringProc();
            break;
        case RangeState::rsCppComment:
            ansiCppProc();
            break;
        case RangeState::rsMultiLineDirective:
            directiveEndProc();
            break;
        case RangeState::rsMultiLineString:
            stringEndProc();
            break;
        case RangeState::rsRawStringEscaping:
        case RangeState::rsRawStringNotEscaping:
            rawStringProc();
            break;
        case RangeState::rsStringEscapeSeq:
        case RangeState::rsMultiLineStringEscapeSeq:
            stringEscapeSeqProc();
            break;
        case RangeState::rsChar:
            if (mLine[mRun]=='\'') {
                mRange.state = rsUnknown;
                mTokenId = TokenId::Char;
                mRun+=1;
            } else {
                asciiCharProc();
            }
            break;
        case RangeState::rsDefineIdentifier:
            defineIdentProc();
            break;
        case RangeState::rsDefineRemaining:
            defineRemainingProc();
            break;
        default:
            mRange.state = RangeState::rsUnknown;
            if (mLine[mRun] == 'R' && mLine[mRun+1] == '"') {
                mRun+=2;
                rawStringProc();
            } else if ((mLine[mRun] == 'L' || mLine[mRun] == 'u' || mLine[mRun]=='U') && mLine[mRun+1]=='\"') {
                mRun+=1;
                stringStartProc();
            } else if (mLine[mRun] == 'u' && mLine[mRun+1] == '8' && mLine[mRun+2]=='\"') {
                mRun+=2;
                stringStartProc();
            } else
                processChar();
        }
    } while (mTokenId!=TokenId::Null && mRun<=mTokenPos);
}

void CppHighlighter::setLine(const QString &newLine, int lineNumber)
{
    mLineString = newLine;
    mLine = mLineString.data();
    mLineNumber = lineNumber;
    mRun = 0;
    mRange.leftBraces = 0;
    mRange.rightBraces = 0;
    mRange.firstIndentThisLine = mRange.indents.length();
    mRange.matchingIndents.clear();
    next();
}

bool CppHighlighter::isKeyword(const QString &word)
{
    return Keywords.contains(word);
}

TokenType CppHighlighter::getTokenType()
{
    switch(mTokenId) {
    case TokenId::Comment:
        return TokenType::Comment;
    case TokenId::Directive:
        return TokenType::PreprocessDirective;
    case TokenId::Identifier:
        return TokenType::Identifier;
    case TokenId::Key:
        return TokenType::Keyword;
    case TokenId::Space:
        switch (mRange.state) {
        case RangeState::rsAnsiC:
        case RangeState::rsAnsiCAsm:
        case RangeState::rsAnsiCAsmBlock:
        case RangeState::rsAsm:
        case RangeState::rsAsmBlock:
        case RangeState::rsDirectiveComment:
        case RangeState::rsCppComment:
            return TokenType::Comment;
        case RangeState::rsDirective:
        case RangeState::rsMultiLineDirective:
            return TokenType::PreprocessDirective;
        case RangeState::rsString:
        case RangeState::rsMultiLineString:
        case RangeState::rsStringEscapeSeq:
        case RangeState::rsMultiLineStringEscapeSeq:
        case RangeState::rsRawString:
            return TokenType::String;
        case RangeState::rsChar :
            return TokenType::Character;
        default:
            return TokenType::Space;
        }
    case TokenId::String:
        return TokenType::String;
    case TokenId::StringEscapeSeq:
        return TokenType::StringEscapeSequence;
    case TokenId::RawString:
        return TokenType::String;
    case TokenId::Char:
        return TokenType::Character;
    case TokenId::Symbol:
        return TokenType::Symbol;
    case TokenId::Number:
        return TokenType::Number;
    default:
        return TokenType::Default;
    }
}

void CppHighlighter::setState(const HighlighterState& rangeState)
{
    mRange = rangeState;
    // current line's left / right parenthesis count should be reset before parsing each line
    mRange.leftBraces = 0;
    mRange.rightBraces = 0;
    mRange.firstIndentThisLine = mRange.indents.length();
    mRange.matchingIndents.clear();
}

void CppHighlighter::resetState()
{
    mRange.state = RangeState::rsUnknown;
    mRange.braceLevel = 0;
    mRange.bracketLevel = 0;
    mRange.parenthesisLevel = 0;
    mRange.leftBraces = 0;
    mRange.rightBraces = 0;
    mRange.indents.clear();
    mRange.firstIndentThisLine = 0;
    mRange.matchingIndents.clear();
    mAsmStart = false;
}

HighlighterClass CppHighlighter::getClass() const
{
    return HighlighterClass::CppHighlighter;
}

QString CppHighlighter::getName() const
{
    return SYN_HIGHLIGHTER_CPP;
}

QString CppHighlighter::languageName()
{
    return "cpp";
}

HighlighterLanguage CppHighlighter::language()
{
    return HighlighterLanguage::Cpp;
}

HighlighterState CppHighlighter::getState() const
{
    return mRange;
}

bool CppHighlighter::isIdentChar(const QChar &ch) const
{
    return ch=='_' || ch.isDigit() || ch.isLetter();
}

QSet<QString> CppHighlighter::keywords() const
{
    return Keywords;
}

QString CppHighlighter::foldString()
{
    return "...}";
}

}
