--Stack spec from the Ada notes in unit6_ada_ii.pdf
--has been adapated to a different data type for use in maze solving

package maze_stack is
    type element is array(1..2) of integer;
    procedure push( x : in element);
    procedure pop( x : out element);
    function stack_is_empty return Boolean;
    function stack_top return element;
    procedure reset_stack;
end maze_stack;
