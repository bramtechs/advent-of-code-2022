<?php

include "utils.php";

$lines = readinput("inputs/input12_sample.txt");

$map = array ();

$width = strlen($lines[0]);
$height = count($lines);

for ($y = 0; $y < $height; $y++){
    $map[] = array();
    for ($x = 0; $x < $width; $x++){
        $ch = $lines[$y][$x];
        switch ($ch){
            case 'S':
                $ch = 'a'; 
                break;
            case 'E':
                $ch = 'z'; 
                break;
        }

        $val = ord($ch);
        if ($val == 13 || $val == 10){
            continue;
        }
        $val -= 97;

        $map[$x][$y] = $val;
        echo $ch . $map[$x][$y] . '|';
    }
    echo "\n";
}

?>
