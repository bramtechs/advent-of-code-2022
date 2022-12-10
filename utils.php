<?php

function readinput(string $path): array {
    $lines = array();
    $my_file = fopen($path, "r") or die("Unable to open puzzle input!");
    while(!feof($my_file)) {
        $line = fgets($my_file);
        if (!empty($line)){
            $lines[] = $line;
        }
    }
    fclose($my_file);
    return $lines;
}

?>
