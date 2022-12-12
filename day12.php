<?php

include "utils.php";

$input = readinput_single("inputs/input12.txt");

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

function is_accessible(int $origin, int $dest): bool
{
    global $map, $visits, $width;
    assert($origin >= 0 && $origin < count($map), "Origin out of bounds!");

    if ($dest < 0 || $dest >= count($map)) {
        return false;
    }

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

function is_peak(int $i): bool
{
    global $map;
    $peak = ord('z') - 97;
    return $map[$i] == $peak;
}

$paths = array();
$valid_paths = array();

function try_take_route(array $path, int $origin, int $offset, bool $ghost): bool
{
    global $paths;


    if (is_accessible($origin, $origin + $offset)) {
        if ($ghost) {
            $new_path = $path; // copy
            $paths[] = $new_path;
            walk($new_path, $origin + $offset);
        } else {
            walk($path, $origin + $offset);
            return true;
        }
    }
    return false;
}

function walk(array $path, int $pos)
{
    global $map, $paths, $valid_paths, $visits, $width;

    // mark i've been here
    $visits[$pos] = true;
    $path[] = $pos;

    // check if peak
    if (is_peak($pos)) {
        // i'm done, no more movement needed!
        $steps = count($path);
        $valid_paths[] = $path;
        echo "path reached peak $pos with $steps steps!\n";
        return;
    }

    // take first available neighbor fork all the other available neighbors

    $ghost = try_take_route($path, $pos, 1, false); // west
    $ghost = try_take_route($path, $pos, -1, $ghost); // east
    $ghost = try_take_route($path, $pos, -$width, $ghost); // north
    $ghost = try_take_route($path, $pos, $width, $ghost); // south

    // if no available neighbors, don't do anything 
}

array_push($paths, array());
walk($paths[0], $cur_pos);

// get valid path with least amount of steps

$least_steps = PHP_INT_MAX;
foreach ($valid_paths as $path) {
    $count = count($path);
    if ($count < $least_steps) {
        $least_steps = $count;
    }
}
echo "$least_steps\n";
