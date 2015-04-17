%{
#include "y.tab.h"
%}

%%

"a"*   { return(A_TOK); }
"b"*   { return(B_TOK); }
[ \t]  { /*NOOP*/       }
\n     { return(0);     }
