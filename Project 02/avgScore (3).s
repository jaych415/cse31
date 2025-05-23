.data 

# === Memory Allocation ===
orig: .space 100	      # Reserve 100 bytes for up to 25 integers (original scores)
sorted: .space 100	      # Reserve 100 bytes for a copy of scores to sort

# === User Prompt Strings ===
str0: .asciiz "Enter the number of assignments (between 1 and 25): "  # Ask for assignment count
str1: .asciiz "Enter score: "                                         # Ask for a single score
str2: .asciiz "Original scores: "                                     # Label for printing original array
str3: .asciiz "Sorted scores (in descending order): "                 # Label for printing sorted array
str4: .asciiz "Enter the number of (lowest) scores to drop: "         # Ask for how many scores to drop
str5: .asciiz "Average (rounded down) with dropped scores removed: "  # Label before average is printed
allDroppedStr: .asciiz "All scores dropped!\n"                        # Message if all scores are dropped
newLine: .asciiz "\n"                                                 # Newline character for formatting
space: .asciiz " "                                                    # Space between printed values

.text 
main: 
	addi $sp, $sp, -4        # Make space on stack to save return address
	sw $ra, 0($sp)           # Save return address to stack

# === Get number of assignments ===
get_num_assignments:
    li $v0, 4 
    la $a0, str0 
    syscall                  # Print prompt to ask for number of assignments

    li $v0, 5
    syscall                  # Read integer from user input
    move $s0, $v0            # Save number of assignments to $s0

    # Input validation: must be in [1, 25]
    blt $s0, 1, get_num_assignments
    bgt $s0, 25, get_num_assignments

# === Read scores into array ===
	move $t0, $zero          # Initialize loop counter (i = 0)
	la $s1, orig             # Load base address of original array into $s1
	la $s2, sorted           # Load base address of sorted array into $s2

loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall                  # Print prompt to enter score

	sll $t1, $t0, 2          # Compute offset = i * 4
	add $t1, $t1, $s1        # Get address of orig[i]

	li $v0, 5
	syscall                  # Read next score
	sw $v0, 0($t1)           # Store score in orig[i]

	addi $t0, $t0, 1         # i++
	bne $t0, $s0, loop_in    # Loop until i == num_assignments

# === Sort the array (selection sort) ===
	move $a0, $s0            # Pass number of scores in $a0
	jal selSort              # Call sorting subroutine

# === Print original array ===
	li $v0, 4 
	la $a0, str2 
	syscall                  # Print label

	move $a0, $s1            # $a0 = base address of original array
	move $a1, $s0            # $a1 = number of scores
	jal printArray           # Call array printing function

# === Print sorted array ===
	li $v0, 4 
	la $a0, str3 
	syscall                  # Print label

	move $a0, $s2            # $a0 = base address of sorted array
	move $a1, $s0            # $a1 = number of scores
	jal printArray           # Call print function

# === Ask user how many scores to drop ===
get_drop_count:
	li $v0, 4 
	la $a0, str4 
	syscall                  # Prompt user

	li $v0, 5
	syscall 
	move $t9, $v0            # Save drop count to $t9

	# Validate drop count
	blt $t9, 0, get_drop_count
	bgt $t9, $s0, get_drop_count

	beq $t9, $s0, all_dropped  # Special case: all scores are dropped

# === Calculate average of top scores ===
	sub $a1, $s0, $t9        # Compute number of remaining scores = total - dropped
	move $a0, $s2            # Use sorted array for averaging
	jal calcSum              # Calculate sum of remaining top scores The calcSum function recursively computes the sum of the first $a1 integers in an array starting at $a0.
				#If $a1 <= 0, it returns 0 (base case).
				#Otherwise, it calls itself to sum the first $a1 - 1 elements, then adds the value at index $a1 - 1.
				#The final result is returned in $v0.
				#It uses the stack to save/restore $ra, $a1, and $t0 during recursion.

	div $v0, $a1             # Divide total sum by number of kept scores
	mflo $t1                 # Get quotient (rounded down) in $t1

	li $v0, 4
	la $a0, str5
	syscall                  # Print message before average

	li $v0, 1
	move $a0, $t1
	syscall                  # Print average

	j end_program            # Exit

# === Special case: All scores dropped ===
all_dropped:
	li $v0, 4
	la $a0, allDroppedStr
	syscall                  # Notify user all scores were dropped

# === Exit program ===
end_program:
	lw $ra, 0($sp)           # Restore return address
	addi $sp, $sp, 4         # Restore stack
	li $v0, 10
	syscall                  # Exit

# === Subroutine: printArray ===
# Prints all values in an array with spaces between
printArray:
	addi $s0, $zero, 0       # i = 0
	addi $sp, $sp, -4
	sw $a0, 0($sp)           # Save array base address

	move $t0, $a0            # Array pointer
	move $t1, $a1            # Count of elements

while:
	beq $s0, $a1, endWhile   # If i == count, done
	li $v0, 1
	lw $a0, 0($t0)
	syscall                  # Print number

	li $v0, 4
	la $a0, space
	syscall                  # Print space

	addi $t0, $t0, 4         # Move to next element
	addi $s0, $s0, 1         # i++
	j while

endWhile:
 	li $v0, 4
 	la $a0, newLine
	syscall                  # Print newline
	lw $a0, 0($sp)           # Restore original $a0
	addi $sp, $sp, 4
	jr $ra

# === Subroutine: selSort ===
# Sorts the array in descending order using selection sort
selSort:
	add $t2, $zero, $zero    # i = 0
	add $t3, $a0, $zero      # total = $a0

# --- Copy original array to sorted array ---
copy_array_loop:
	sll $t1, $t2, 2
	add $t4, $t1, $s2        # sorted[i]
	add $t5, $t1, $s1        # orig[i]
	lw $t6, 0($t5)           
	sw $t6, 0($t4)           # sorted[i] = orig[i]

	addi $t2, $t2, 1
	bne $t2, $t3, copy_array_loop  # Loop until all copied

# --- Edge case: only 1 element, skip sorting ---
	addi $t0, $zero, 1
	beq $a0, $t0, back

	add $t2, $zero, $zero     # outer loop i = 0
	addi $t3, $a0, -1         # loop until i = n - 1

sort_array_loop:
	add $t0, $t2, $zero       # maxIndex = i
	addi $t4, $t2, 1          # j = i + 1
	add $t5, $a0, $zero       # total = $a0

# --- Inner loop: find max index ---
sort_inner:
	sll $t1, $t4, 2
	add $t1, $t1, $s2
	lw $t6, 0($t1)            # temp = sorted[j]

	sll $t1, $t0, 2
	add $t1, $t1, $s2
	lw $t7, 0($t1)            # current max = sorted[maxIndex]

	bgt $t6, $t7, newMaxIndex # if sorted[j] > sorted[maxIndex]

If:
	addi $t4, $t4, 1
	bne $t4, $t5, sort_inner  # repeat inner loop

	# Swap max with i
	sll $t1, $t0, 2
	add $t1, $t1, $s2
	lw $t7, 0($t1)            # temp = sorted[maxIndex]

	sll $t1, $t2, 2
	add $t1, $t1, $s2
	lw $t6, 0($t1)            # sorted[i]
	sw $t7, 0($t1)            # sorted[i] = temp

	sll $t1, $t0, 2
	add $t1, $t1, $s2
	sw $t6, 0($t1)            # sorted[maxIndex] = sorted[i]

	addi $t2, $t2, 1          # i++
	bne $t2, $t3, sort_array_loop

back:
	jr $ra

newMaxIndex:
	add $t0, $t4, $zero       # maxIndex = j
	j If

# === Recursive Function: calcSum ===
# Recursively computes the sum of the first $a1 elements in array at $a0
calcSum:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $a1, -4($sp)
	sw $t0, -8($sp)

	ble $a1, $zero, returnZero # base case: if n <= 0, return 0

	addi $a1, $a1, -1
	jal calcSum                # sum = calcSum(arr, n - 1)
	move $t0, $v0

	sll $t1, $a1, 2
	add $t1, $t1, $a0
	lw $t2, 0($t1)             # t2 = arr[n - 1]

	add $v0, $t0, $t2          # result = sum + arr[n - 1]
	j end

returnZero:
	add $v0, $zero, $zero      # return 0
	j end

end:
	lw $ra, 0($sp)
	lw $a1, -4($sp)
	lw $t0, -8($sp)
	addi $sp, $sp, 12
	jr $ra
