<?php
include "utils.php";

$cycle = 0;
$reg_x = 1;
$total_strength = 0;

$lines = readinput("inputs/input10.txt");

function add_cycle(){
    global $cycle;
    global $reg_x;
    global $total_strength;

    $cycle ++;

    // record signal strength
    if ($cycle != 0 && ($cycle + 20) % 40 == 0){
        $strength = $cycle * $reg_x;
        //echo "$cycle * $reg_x = $strength\n";
        $total_strength += $strength;
    }
    //echo "$cycle : $reg_x\n";
}

foreach ($lines as $i => $line) {
    add_cycle();
    if (str_contains($line,"addx")){
        add_cycle(); 

        // boom!!, get value
        $amount = explode(" ",$line,2)[1];
        $reg_x += $amount;
    }
}

echo $total_strength;

?>
