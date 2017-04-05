//master function, set up prelude, finale and IO functions
void emitTM( astTreeNode * tree, string filename );

//evalutes each node then call one of the three following
int nodeEmit( astTreeNode * tree, int offset, int level, bool func );

//emits statements
void stmtEmit( astTreeNode * tree, int offset, int level, bool func );

//emits expressions
void expEmit( astTreeNode * tree, int offset );

//emits arithmetic expressions, whiles and ifs
void emitOP( astTreeNode * tree, int offset );

//writes a single line of TM assembly
void emitRM( string op, int r, int d, int s, string m );
void emitRO( string op, int r, int s, int t, string m );
