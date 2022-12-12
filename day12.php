<?php

include "utils.php";

$input = readinput_single("inputs/input12_sample.txt");

$map = array();
$visits = array();

$width = 0;
$height = 0;

$cur_pos = 0;

for ($i = 0; $i < strlen($input); $i++) {
    $ch = $input[$i];
    if (ord($ch) == 10) {
        if ($width == 0) {
            $width = $i;
        }
        continue;
    }
    switch ($ch) {
        case 'S':
            $ch = 'a';
            $cur_pos = count($map);
            break;
        case 'E':
            $ch = 'z';
            break;
    }
    $val = ord($ch) - 97;
    $map[] = $val;
    $visits[] = false;
}

$height = floor(count($map) / $width);

// var_dump($map);
// echo "$width x $height\n";

# babbies first attempt at depth first search

function is_accessible(int $origin, int $dest): bool
{
    global $map, $visits, $width;
    assert($origin >= 0 && $origin < count($map), "Origin out of bounds!");

    // check if adjacent 
    if (abs(($origin % $width) - ($dest % $width)) <= 1) {

        $orig_height = $map[$origin];
        $dest_height = $map[$dest];
        if ($dest >= 0 && $dest < count($map)) {
            if (!$visits[$dest] && $dest_height <= $orig_height + 1) {
                return true;
            }
        }
    }
    return false;
}

function visit_neighbor(int $i): int | null
{
    global $visits, $dirs, $width, $height;

    if (is_accessible($i, $i + 1)) { // east
        $visits[$i+1] = true;
        echo "east \n";
        return $i+1;
    }
    if (is_accessible($i, $i - 1)) { // west
        $visits[$i-1] = true;
        echo "west \n";
        return $i-1;
    }
    if (is_accessible($i, $i - $width)) { // north
        $visits[$i-$width] = true;
        echo "north \n";
        return $i-$width;
    }
    if (is_accessible($i, $i + $width)) { // south
        $visits[$i+$width] = true;
        echo "south \n";
        return $i+$width;
    }

    // no neighbors found that are in reach and aren't visited
    return null;
}

function is_peak(int $i): bool
{
    global $map;
    $peak = ord('z') - 97;
    return $map[$i] == $peak;
}

$stack = array();
array_push($stack, $cur_pos);

$steps = 0;
while (count($stack) > 0) {
    $neigh = visit_neighbor($cur_pos);
    if ($neigh != null) {
        array_push($stack, $neigh);
        $cur_pos = $neigh;

        if (is_peak($cur_pos)) {
            echo "found peak!\n";
            break;
        }
    } else {
        // backtrack through the stack
        $cur_pos = array_pop($stack);
    }
    //var_dump($stack);
    $steps++;
    assert($steps < 200);
}

echo $steps . "\n";
