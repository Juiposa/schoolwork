with Ada.Text_IO, Ada.Integer_Text_IO, Ada.Strings, Ada.Strings.Fixed;
use Ada.Text_IO, Ada.Integer_Text_IO, Ada.Strings, Ada.Strings.Fixed;
with maze_stack; use maze_stack;
procedure maze_search is
    type maze_type is array(1..50, 1..50) of character;
    x, y : integer; --cursor location
    mazex, mazey : integer; --maze dimensions
    i, j, k, l : integer; --iterators
    maze : maze_type; --the maze itself
    inFile, outFile : file_type;
    inString : string(1..9);
    inChar : character;
    popped : element;
    newElement : element;
begin
    x := 0; y := 0;
    put_line("Maze search.");
    put_line("Enter file name to read from:");
    get(Standard_Input, inString);
    put("Opening file: "); put_line(inString);
    open(inFile, In_File, trim(inString, Both));
    get(inFile, mazex);
    get(inFile, mazey);
    put("Maze dimensions(x,y): "); put(mazex,3); put(mazey,3); New_Line;
    --read in maze and find the start position
    for i in 1..mazey loop
        for j in 1..mazex loop
            Get(inFile, inChar);
            maze(i,j) := inChar;
            if inChar = 'o' then
                x := i; y := j;
            end if;
        end loop;
    end loop;
    if x = 0 or y = 0 then
        put_line("Maze has no start point or is formatted incorrectly.");
    end if;
    put_Line("Inputted maze.");
    for i in 1..mazey loop
        for j in 1..mazex loop
            put(maze(i,j));
        end loop;
        New_Line;
    end loop;
    while maze(x,y) /= 'e' loop
        --first check if any of the adjacent cells is the terminus
        --this if statement is gross
        if maze(x+1,y)='e' or maze(x,y+1)='e' or maze(x-1,y)='e' or maze(x,y-1)='e' then
            exit;
        end if;
        --checks directions to see if it can move and moves to the first open direction
        --priority is E S W N, in that order
        --if it can't move, it'll pop the previous cell and move backwards, marking the dead end along the way
        newElement(1) := x; newElement(2) := y;
        if maze(x+1,y) = '.' then --east
            push(newElement);
            x := x + 1;
            maze(x,y) := 'v';
        elsif maze(x,y+1) = '.' then --south
            push(newElement);
            y := y + 1;
            maze(x,y) := 'v';
        elsif maze(x-1,y) = '.' then --west
            push(newElement);
            x := x - 1;
            maze(x,y) := 'v';
        elsif maze(x,y-1) = '.' then --north
            push(newElement);
            y := y - 1;
            maze(x,y) := 'v';
        else
            maze(x,y) := 'X';
            pop(popped);
            x := popped(1);
            y := popped(2);
        end if;

        if stack_is_empty then
            put_line("Empty stack, cannot find end point.");
            exit;
        end if;
    end loop;

    put_Line("Output.");
    for i in 1..mazey loop
        for j in 1..mazex loop
            put(maze(i,j));
        end loop;
        New_Line;
    end loop;
end;
