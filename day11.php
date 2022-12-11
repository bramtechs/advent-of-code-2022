<?php
include "utils.php";
error_reporting(E_ERROR | E_PARSE);

$worried = 0;

class Monkey {
    public $items = array();
    public string $worried_formula;
    public string $test;
    public int $target_true;
    public int $target_false;

    function throw(){

    }
}

$lines = readinput("inputs/input11_sample.txt");
$i = 0;
$monkeys = array();

while ($i < count($lines)){
    $i++;

    $monkey = new Monkey();
    
    // starting items
    $items = explode(":",$lines[$i])[1];
    $items = trim($items);
    $items = explode(", ",$items);
    foreach ($items as $item){
       $monkey->items[] = intval($item);
    }

    $i++;

    // worried formula (operation)
    $formula = trim(explode(": ",$lines[$i])[1]);
    $monkey->worried_formula = $formula;

    $i++;

    // test
    $test = trim(explode(": ",$lines[$i])[1]);
    $monkey->test = $test;

    $i++;

    $false = intval($lines[$i][strlen($lines[$i])-1]);
    $monkey->target_false = $false;

    $i++;

    $true = intval($lines[$i][strlen($lines[$i])-1]);
    $monkey->target_true = $true;
    
    $monkeys[] = $monkey;

    $i++;
    $i++;

}
var_dump($monkeys);

?>
