<?php

require "Exec.php";
require "Robot.php";

class SolveNine extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/nine/";
    const CAPTCHA_IMG = "https://192.168.1.3/nine/";

    protected function captchaTreatment($contents) {
        return array(
            "power" => "off",
        );
    }

}


$solveOne = new SolveNine("thebug", "thebug9988.-");
$points = 0;
while (true) {
    $points += $solveOne->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}
