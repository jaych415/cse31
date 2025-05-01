        .data
newline: .asciiz "\n"        # Define a null-terminated string for a newline.

        .text
        .globl main         # Declare the main label as global so that the program knows where to start.

main:
        # Note: $s0 contains the initial value. You must set $s0 manually in MARS before running.

        # Copy the initial value from $s0 into $t0.
        move  $t0, $s0       # $t0 = $s0

        # Subtract 7 from $t0 and store the result in $t1.
        addi  $t1, $t0, -7   # $t1 = $t0 - 7

        # Add the values in $t0 and $t1 and store the result in $t2.
        add   $t2, $t1, $t0  # $t2 = $t1 + $t0

        # Add 2 to $t2 and store the result in $t3.
        addi  $t3, $t2, 2    # $t3 = $t2 + 2

        # Add the values in $t3 and $t2 and store the result in $t4.
        add   $t4, $t3, $t2  # $t4 = $t3 + $t2

        # Subtract 28 from $t4 and store the result in $t5.
        addi  $t5, $t4, -28  # $t5 = $t4 - 28

        # Subtract $t5 from $t4 and store the result in $t6.
        sub   $t6, $t4, $t5  # $t6 = $t4 - $t5

        # Add 12 to $t6 and store the result in $t7.
        addi  $t7, $t6, 12   # $t7 = $t6 + 12

        # At this point, $t7 holds the final result of the arithmetic operations.

        # --- this section can be optional: Print the final result in $t7 ---

        # Move the value in $t7 to $a0 for printing.
        move  $a0, $t7       # Prepare the argument for printing (integer in $a0).
        li    $v0, 1         # Load syscall code 1 (print integer) into $v0.
        syscall              # Execute the syscall to print the integer in $a0.

        # Print a newline for clarity.
        la    $a0, newline   # Load the address of the newline string into $a0.
        li    $v0, 4         # Load syscall code 4 (print string) into $v0.
        syscall              # Execute the syscall to print the newline.

        # this part is for exiting the program 
        li    $v0, 10        # Load syscall code 10 (exit program) into $v0.
        syscall              # Execute the syscall to exit.
        
        
        #The code starts with an initial value in \$s0, but then it subtracts, 
        #adds, and adjusts using constants in such a way that the part involving 
        #\$s0 cancels out. First, it subtracts 7 from the initial value and then 
        #adds the original value back, which begins to neutralize the dependency
         #on the input. Later operations combine the results and further cancel 
         #out any trace of the initial value. In the end, only constant values 
         #remain, and these add up to 40, so the final output is always 40.
