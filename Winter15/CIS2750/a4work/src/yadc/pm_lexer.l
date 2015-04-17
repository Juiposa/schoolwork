%{
#include "y.tab.h"
%}

%%

"="     { return EQUALS;  }
[{\(\[] { return L_PAREN; }
[}\)\]] { return R_PAREN; }
"\""    { return QUOTE;   }
";"		{ return COLON;   }
"!"		{ return EXCLAIM; }
"#"	    { return COMMENT; }
","		{ return COMMA;   }
\n		{ return NEWLN;   }
[ \t]*  { /*NOOP       */ }
"EOF"	{ return 0;       }		
[a-zA-z0-9]+ {  yylval.str = strdup(yytext); return WORD; }
