<?php

require "Exec.php";
require "Robot.php";

class SolveThree extends Robot {

    const CAPTCHA_URL = "https://192.168.1.3/three/";
    const CAPTCHA_IMG = "https://192.168.1.3/three/securimage_show.php";

    protected function captchaTreatment(&$image) {
        rename($image, ($image = "$image.png"));

        $gd = imagecreatefrompng($image);
        for ($x = 0; $x< imagesx($gd); $x++) {
            for ($y = 0; $y< imagesy($gd); $y++) {

                /* POG */
                $rgb = imagecolorat($gd, $x, $y);
                list($r, $g, $b) = array(($rgb >> 16) & 0xFF, ($rgb >> 8) & 0xFF, $rgb & 0xFF);

                if($r > 1 || $g < 10 )
                    imagesetpixel($gd, $x, $y, 0xFFFFFF);

            }
        }

        imagepng($gd, $image);

        $subject = Exec::factory("/usr/bin/convert")
                ->setArgument($image)
                ->setArgument("$image.tif")
                ->call();

        unlink($image);
        $image = "$image.tif";

        Exec::factory("/usr/bin/tesseract")
                ->setArgument($image)
                ->setArgument($image)
                ->setStderr("/dev/null")
                ->call();

        $subject = file_get_contents("$image.txt");
        unlink("$image.txt");

        $subject = trim($subject);

        if (!preg_match('/^[A-Za-z0-9]{6}$/', $subject))
            throw new Exception($subject);

        return $subject;
    }

}

$solveTwo = new SolveThree("thebug", "thebug9988.-");
$points = 0;
while (true) {
    try {
        $points += $solveTwo->play() ? 1 : - 1;
        printf("\rPoints: %5d", $points);
    } catch (Exception $e) { }
}
