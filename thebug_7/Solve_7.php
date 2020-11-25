<?php

require "Exec.php";
require "Robot.php";

class SolveSeven extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/seven/";
    const CAPTCHA_IMG = "https://192.168.1.3/seven/";

    protected function captchaTreatment($contents) {
        $correspondence = array(
            "1"  => "A",
            "10" => "M",
            "11" => "N",
            "12" => "R",
            "13" => "S",
            "14" => "G",
            "15" => "H",
            "16" => "I",
            "17" => "X",
            "18" => "J",
            "19" => "K",
            "20" => "9",
            "21" => "0",
            "22" => "O",
            "23" => "P",
            "24" => "Q",
            "25" => "T",
            "26" => "2",
            "27" => "U",
            "28" => "V",
            "29" => "4",
            "2"  => "B",
            "30" => "5",
            "31" => "W",
            "32" => "6",
            "33" => "Z",
            "34" => "7",
            "3"  => "C",
            "4"  => "3",
            "5"  => "E",
            "6"  => "1",
            "7"  => "F",
            "8"  => "Y",
            "9"  => "L",
        ); 
        if (!preg_match('/input=(\d+),(\d+),(\d+),(\d+),(\d+)/', $contents, $match))
            return null;
        $subject = "";
        for($i = 1; $i <= 5; $i++)
            $subject .= $correspondence[$match[$i]];
        return $subject;
    }

}


$solveOne = new SolveSeven("thebug", "thebug9988.-");
$points = 0;
while (true) {
    $points += $solveOne->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}
