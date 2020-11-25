<?php

require "Exec.php";
require "Robot.php";

class SolveTen extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/ten/";
    const CAPTCHA_IMG = "https://192.168.1.3/ten/";

    protected function captchaTreatment($contents) {
        return array(
            "__ec_i" => "ec.1290960242.2d9ee5738ecade75cdc445605141cd3b",
            "__ec_s" => "4YX17"
        );
    }

}


//$solveOne = new SolveTen("thebug", "thebug9988.-");
$solveOne = new SolveTen("", "");
$points = 0;
while (true) {
    $points += $solveOne->play() ? 1 : - 1;
    printf("\rPoints: %5d", $points);
}
