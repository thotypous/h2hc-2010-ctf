<?php

require "Exec.php";
require "Robot.php";

class SolveFour extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/four/";
    const CAPTCHA_IMG = "https://192.168.1.3/four/";

    protected function captchaTreatment($contents) {
    }

}


$solveOne = new SolveFour("thebug", ".-");
$points = 0;
while (true) {
    $points += $solveOne->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}
