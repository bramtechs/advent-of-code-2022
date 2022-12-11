<?php
include "utils.php";
error_reporting(E_ERROR | E_PARSE);

$monkeys = array();

class Monkey {
    public $items = array();
    public string $worried_formula;
    public int $test_mod;
    public int $target_true;
    public int $target_false;
    public int $inspections;

    function calc_worried(int $worry): int{
        $formula  = str_replace("old",$worry,$this->worried_formula);
        $new_worry = eval('return ' . $formula . ';'); // dangerous
        return $new_worry;
    }

    function take_turn(){

        // calculate worry
        while (count($this->items) > 0){
            $next_item = array_shift($this->items);
            $next_item = $this->calc_worried($next_item);
            $this->inspections++;

            // monkey get's bored
            $next_item = floor($next_item / 3);

            // do test
            if ($next_item % $this->test_mod == 0){
                $this->throw_towards($next_item, $this->target_true);
            }else{
                $this->throw_towards($next_item, $this->target_false);
            }
        }
    }

    function catch_item($item){
        $this->items[] = $item;
    }

    function throw_towards($item, $monkey_id){
        global $monkeys;
        // echo "Throwing item " . $item . " towards " . $monkey_id . "\n";
        $monkeys[$monkey_id]->catch_item($item);
    }

    function print_inventory($id){
        echo "Monkey $id: ";
        foreach ($this->items as $item){
            echo "$item, ";
        }
        echo "\n";
    }
}

$lines = readinput("inputs/input11.txt");
$i = 0;

while ($i < count($lines)){
    $i++;

    $monkey = new Monkey();
    $monkey->inspections = 0;
    
    // starting items
    $items = explode(":",$lines[$i])[1];
    $items = trim($items);
    $items = explode(", ",$items);
    foreach ($items as $item){
       $monkey->items[] = intval($item);
    }

    $i++;

    // worried formula (operation)
    $formula = explode(": ",$lines[$i])[1];
    $formula = trim(explode(" = ",$lines[$i])[1]);
    $monkey->worried_formula = $formula;

    $i++;

    // test
    $test = trim(explode("by ",$lines[$i])[1]);
    $monkey->test_mod = intval($test);

    $i++;

    $true = trim($lines[$i]);
    $true = $true[strlen($true)-1];
    $true = intval($true);
    $monkey->target_true = $true;

    $i++;

    $false = trim($lines[$i]);
    $false = $false[strlen($false)-1];
    $false = intval($false);
    $monkey->target_false = $false;
    
    $monkeys[] = $monkey;

    $i++;
    $i++;
}

// var_dump($monkeys);

function print_round(int $round){
    echo "\n";
    echo "Round: $round \n";
    echo "========================\n";
    global $monkeys;
    $id = 0;
    foreach ($monkeys as $monkey){
        $monkey->print_inventory($id);
        $id++;
    }
}

// print_round(0);
for ($i = 1; $i <= 20; $i++){
    foreach ($monkeys as $monkey){
        $monkey->take_turn();
    }
    // print inventories
    // print_round($i);
}

// sum of two most active monkeys
$inspections = array();
foreach ($monkeys as $monkey){
    $inspections[] = $monkey->inspections;
}
rsort($inspections);

$monkey_business = $inspections[0] * $inspections[1];
echo "$monkey_business\n";
?>
