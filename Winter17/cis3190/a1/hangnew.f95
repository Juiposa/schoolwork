!      GAME OF HANGMAN BY DAVE AHL, DIGITAL
!      BASED ON A BASIC PROGRAM WRITTEN BY KEN AUPPERLE
!            HALF HALLOW HILLS H.S. DIX HILLS NY
!      CONVERTED TO FORTRAN 77 BY M.WIRTH, APRIL 2012
!      REENGINEERED INTO FORTRAN 90/95 BY JEFFREY-DAVID KAPP, JANUARY 2017
program hangman

   character :: gallows(12,12)
   character :: display(20), letters(26), guess, response
   character(20) :: answer, word_guess
   integer :: used_words(50)
   integer :: q, incorrect_guesses, i, j, num_words, total_guesses, r, length, guess_valid
   real :: rnd

   character(20), dimension(50) :: dict = [character(20) :: 'gum','sin','for','cry','lug','bye','fly','ugly', &
                                                            'each','from','work','talk','with','self',  &
                                                            'pizza','thing','feign','fiend','elbow','fault', &
                                                            'dirty','budget','spirit','quaint','maiden', &
                                                            'escort','pickax','example','tension','quinine', &
                                                            'kidney','replica','sleeper','triangle', &
                                                            'kangaroo','mahogany','sergeant','sequence', &
                                                            'moustache','dangerous','scientist','different', &
                                                            'quiescent','magistrate','erroneously', &
                                                            'loudspeaker','phytotoxic','matrimonial', &
                                                            'parasympathomimetic','thigmotropism']

     write (*,*) "The Game of Hangman"
     !word count initialisation
     count=1
     num_words=50

     do while ( count < num_words ) !master loop
         !start; variable initialisation
         !most variables reinitalised after each word
         do i = 1,12
               do j = 1,12
                   gallows(i,j) = " "
             end do
         end do
         do i = 1,20
             display(i) = "-"
         end do
         do i = 1,26
             letters(i) = " "
         end do
         do i = 1,50
             used_words(i) = 0
         end do
         do i = 1,12
             gallows(i,1) = "x"
         end do
         do j = 1,7
             gallows(1,j) = "x"
         end do
         gallows(2,7) = "x"
         incorrect_guesses = 0
         word_complete = 0
         !end; variable initialisation

         do i = 1,50 !picking a word
             rnd=rand()
             q=ceiling(rnd*50)
             if (used_words(q) == 0) then
                 used_words(q) = 1
                 count=count+1
                 total_guesses=0
                 exit
             end if
         end do
         answer = dict(q)
         length = len_trim(answer)
         write (*,*) display(1:l)

         do while ( incorrect_guesses < 10) !word loop
             guess_valid = 0
             r=0
             do while ( guess_valid == 0) !guess validation loop
                 call display_letters(letters)
                 write (*,*) " "
                 write (*,*) "What is your guess? "
                 read (*,*) guess
                 do i = 1,26 !guess verification
                     if (letters(i) == " ") then
                         total_guesses=total_guesses+1
                         letters(i) = guess
                         guess_valid = 1
                         exit
                     else if (letters(i) == guess) then
                         write (*,*) "You guessed that letter before."
                         exit
                     end if
                 end do
             end do


             do i = 1,length !checking if the user's guess is in the word
                 if (answer(i:i) == guess) then
                     display(i) = guess
                     r=r+1
                 end if
             end do
             if (r == 0) then !if the user's guess isnt present in the word
                 write (*,*) "Sorry, that letter isn't in the word."
                 incorrect_guesses=incorrect_guesses+1;
                 call update_gallows(incorrect_guesses, gallows) !give the poor victim another body part
                 if (incorrect_guesses == 10) then
                     write (*,*) "Sorry, you loose. The word was ", answer
                     write (*,*) "You missed that one."
                 end if
             else !else it is in the word
                 do i = 1,length !check if word has been completed
                     if (display(i) == "-") then
                         !jump out of loop if it hasn't been
                         exit
                     end if
                 end do
                 if ( i < length ) then !word's not done
                     write (*,*) display(1:length)
                     write (*,*) "What is your guess for the word? "
                     read (*,*) word_guess
                     if (answer .eq. word_guess) then
                         write (*,*) "Right! It took you ",total_guesses," guesses."
                         exit
                     else
                         write (*,*) "Wrong. Try another letter."
                     end if
                 else !it is done
                     write (*,*) "You found the word: ", answer
                     exit
                 end if
             end if
         end do !end word loop

         if (count >= num_words) then
             write (*,*) "You did all the words"
             write (*,*) "Ending..."
         else
             write (*,*) "Do you want another word? (y/n) "
             read (*,*) response
             if (response == "n") then
                 write (*,*) "It's been fun! bye for now."
                 exit
             end if
         end if
     end do !end master loop
end

!sub routine - updating the victim with extra body parts based on the number of incorrect guesses and informing the player
subroutine update_gallows( incorrect_guesses_s, gallows_s )
    integer :: incorrect_guesses_s
    character :: gallows_s(12,12)
    integer :: i, j
    select case (incorrect_guesses_s)
        case (1)
            write (*,*) "First we draw a head."
            gallows_s(3,6) = "-"; gallows_s(3,7) = "-"; gallows_s(3,8) = "-"; gallows_s(4,5) = "(";
            gallows_s(4,6) = "."
            gallows_s(4,8) = "."; gallows_s(4,9) = ")"; gallows_s(5,6) = "-"; gallows_s(5,7) = "-";
            gallows_s(5,8) = "-"
        case (2)
            write (*,*) "Now we draw a body."
            do i = 6,9
                gallows_s(i,7) = "x"
            end do
        case (3)
            write (*,*) "Next we draw an arm."
            do i = 4,7
                gallows_s(i,i-1) = "\"
            end do
        case (4)
            write (*,*) "This time it's the other arm."
            gallows_s(4,11) = "/"; gallows_s(5,10) = "/"; gallows_s(6,9) = "/"; gallows_s(7,8) = "/";
        case (5)
            write (*,*) "Now, let's draw the right leg."
            gallows_s(10,6) = "/"; gallows_s(11,5) = "/";
        case (6)
            write (*,*) "This time we draw the left leg."
            gallows_s(10,8) = "\"; gallows_s(11,9) = "\";
        case (7)
            write (*,*) "Now we put up a hand."
            gallows_s(3,11) = "\";
        case (8)
            write (*,*) "Next the other hand."
            gallows_s(3,3) = "/"
        case (9)
            write (*,*) "Now we draw one foot."
            gallows_s(12,10) = "\"; gallows_s(12,11) = "-";
        case (10)
            write (*,*) "Here's the other foot -- you're hung!!."
            gallows_s(12,3) = "-"; gallows_s(12,4) = "/"
    end select
    do i = 1,12
        write (*,*) (gallows_s(i,j),j=1,12)
    end do
    return
end subroutine
!---

!sub routine - displaying guessed letters
subroutine display_letters( letters_s )
    character :: letters_s(26)
    integer :: i
    write (*,*) "Here are the letters you used: "
    do i = 1,26
        if (letters_s(i) == ' ') then
            exit
        else
            write (*,'(aa$)') letters_s(i),"," !I have no idea what this is doing
        end if
    end do
    return
end subroutine
!---
