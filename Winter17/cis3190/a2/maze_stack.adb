--Stack definition from the Ada notes in unit6_ada_ii.pdf
--has been adaptaed to a different data type for use in maze solving (int arrays of size 6)

with Ada.Text_IO; use Ada.Text_IO;

package body maze_stack is
    type list is array(1..2304) of element;
    type stack is
        record
            item : list;
            top : natural := 0;
        end record;
    st : stack;

    procedure push( x : in element) is
    begin
        if st.top = 100 then
            put_line("stack is full");
        else
            st.top := st.top + 1;
            st.item(st.top) := x;
        end if;
    end push;

    procedure pop( x : out element) is
    begin
        if st.top = 0 then
            put_line("stack is empty");
        else
            x := st.item(st.top);
            st.top := st.top - 1;
        end if;
    end pop;

    function stack_is_empty return Boolean is
    begin
        return st.top = 0;
    end stack_is_empty;

    function stack_top return element is
    begin
        if st.top = 0 then
            put_line("stack is empty");
            return (0,0,0,0,0,0);
        else
            return st.item(st.top);
        end if;
    end stack_top;

    procedure reset_stack is
    begin
        st.top := 0;
    end reset_stack;
end maze_stack;
