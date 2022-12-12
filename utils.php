<?php

function readinput(string $path): array {
    $lines = array();
    $my_file = fopen($path, "r") or die("Unable to open puzzle input!");
    while(!feof($my_file)) {
        $line = fgets($my_file);
        if (!empty($line)){
            $lines[] = trim($line);
        }
    }
    fclose($my_file);
    return $lines;
}

function readinput_single(string $path): string {
    $my_file = fopen($path, "r") or die("Unable to open puzzle input!");
    $content = "";
    while(!feof($my_file)) {
        $line = fgets($my_file);
        if (!empty($line)){
            $content = $content . str_replace("\r","",$line);
        }
    }
    return $content;
}

?>
