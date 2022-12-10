<?php
include "utils.php";

$screen_width = 40;
$screen_height = 6;

$cycle = 0;
$reg_x = 1;
$total_strength = 0;

$lines = readinput("inputs/input10.txt");
$crt = array();

function is_sprite(int $x): bool{
    global $reg_x;
    return $x >= $reg_x-1 && $x <= $reg_x+1;
}

function add_cycle(): void{
    global $cycle, $reg_x, $crt, $total_strength;
    global $screen_width;

    $crt[] = is_sprite($cycle % $screen_width);

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

// part one
echo $total_strength . PHP_EOL;

// part two: print lcd
for ($y = 0; $y < $screen_height; $y++){
    for ($x = 0; $x < $screen_width ; $x++){
        $i = $y * $screen_width + $x;
        if ($crt[$i]){
            echo '#';
        }else{
            echo ' ';
        }
    }
    echo PHP_EOL;
}

?>
