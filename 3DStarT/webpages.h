const char notfound[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>3DStarT</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, minimum-scale=0.10">
  <meta name='mobile-web-app-capable' content='yes'>
  <meta http-equiv="refresh" content="3; url=/">
  <meta name='theme-color' content='#000'>
  <link rel='icon' sizes='256x256' href='https://esp.3dstar.ro/favicon.png'>
</head>
<body style="background-color:#000;color:#fff;text-align:center;">
    <h2>3DStarT</h2>
    <br><br>
    <h3>Page not found<br><br>Click button or wait for page reload.</h3>
    <form action="/">
        <input type="submit" value="Main menu">
    </form>
    <br>
    <hr><br>
    <a href="https://3dstar.ro/">3DStar</a> -
    <a href="https://github.com/cctweaker/3DStarT">GitHub</a>
    <br><br><br>
</body>
</html>
)=====";

const char restart[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>3DStarT</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, minimum-scale=0.10">
  <meta name='mobile-web-app-capable' content='yes'>
  <meta http-equiv="refresh" content="10; url=/">
  <meta name='theme-color' content='#000'>
  <link rel='icon' sizes='256x256' href='https://esp.3dstar.ro/favicon.png'>
</head>
<body style="background-color:#000;color:#fff;text-align:center;">
    <h2>3DStarT<br>restart</h2>
    <br><br>
    <h3> Click button or wait for auto reload...</h3>
    <form action="/">
        <input type="submit" value="Main menu">
    </form>
    <br>
    <hr><br>
    <a href="https://3dstar.ro/">3DStar</a> -
    <a href="https://github.com/cctweaker/3DStarT">GitHub</a>
    <br><br><br>
</body>
</html>
)=====";

const char format[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>3DStarT</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, minimum-scale=0.10">
  <meta name='mobile-web-app-capable' content='yes'>
  <meta name='theme-color' content='#000'>
  <link rel='icon' sizes='256x256' href='https://esp.3dstar.ro/favicon.png'>
</head>
<body style="background-color:#000;color:#fff;text-align:center;">
    <h2>3DStarT<br><br><br>Settings erased!</h2>
    <br>
    <h3>Connect to wifi: "3DStarT"<br>with password "abcd1234"<br>to begin the setup.</h3>
    <br><br><br><br><br>
    <hr><br>
    <a href="https://3dstar.ro/">3DStar</a> -
    <a href="https://github.com/cctweaker/3DStarT">GitHub</a>
    <br><br><br>
</body>
</html>
)=====";

const char update[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>3DStarT</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, minimum-scale=0.10">
  <meta name='mobile-web-app-capable' content='yes'>
  <meta http-equiv="refresh" content="30; url=/">
  <meta name='theme-color' content='#000'>
  <link rel='icon' sizes='256x256' href='https://esp.3dstar.ro/favicon.png'>
</head>
<body style="background-color:#000;color:#fff;text-align:center;">
    <h2>3DStarT</h2>
    <br>
    <h3>Performing firmware update...</h3>
    <br><br>
    <h3> Click button or wait for auto reload...</h3>
    <form action="/">
        <input type="submit" value="Main menu">
    </form>
    <br>
    <hr><br>
    <a href="https://3dstar.ro/">3DStar</a> -
    <a href="https://github.com/cctweaker/3DStarT">GitHub</a>
    <br><br><br>
</body>
</html>
)=====";

const char page_header[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>3DStarT</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, minimum-scale=0.10">
  <meta name='mobile-web-app-capable' content='yes'>
  <meta name='theme-color' content='#000'>
  <link rel='icon' sizes='256x256' href='https://esp.3dstar.ro/favicon.png'>
</head>
<body style="background-color:#000;color:#fff;text-align:center;">
)=====";

const char page_header_mac[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <title>3DStarT</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, minimum-scale=0.10">
  <meta name='mobile-web-app-capable' content='yes'>
  <meta name='theme-color' content='#000'>
  <style>input[type=text]{width:2em;}</style>
  <link rel='icon' sizes='256x256' href='https://esp.3dstar.ro/favicon.png'>
</head>
<body style="background-color:#000;color:#fff;text-align:center;">
)=====";

const char page_footer[] PROGMEM = R"=====(
<hr><br>
<a href="https://3dstar.ro/">3DStar</a> -
<a href="https://github.com/cctweaker/3DStarT">GitHub</a>
<br><br><br>
</body>
</html>
)=====";

const char form_buttons[] PROGMEM = R"=====(
        <input type="submit" value="Submit">
        <br><br>
        <input type="submit" name="save" value="Save config">
    </form>
    <br>
    <form action="/">
        <input type="submit" value="Back">
    </form>
    <br>
)=====";

const char form_button_back[] PROGMEM = R"=====(
    <br>
    <form action="/">
        <input type="submit" value="Back">
    </form>
    <br>
)=====";

const char html_hr[] PROGMEM = R"=====(
<hr>
)=====";

const char html_table_i[] PROGMEM = R"=====(
<table align="center"><tr>
)=====";

const char html_table_s[] PROGMEM = R"=====(
</tr></table>
)=====";

const char html_table_tr[] PROGMEM = R"=====(
</tr><tr>
)=====";

const char html_table_tr_hr[] PROGMEM = R"=====(
</tr><tr><td colspan="2"><hr></td></tr><tr>
)=====";

const char form_start[] PROGMEM = R"=====(
<form>
)=====";

const char form_text_field_string[] PROGMEM = R"=====(
%s<br><input type="text" name="%s" value="%s"><br><br>
)=====";

const char form_text_field_string_min[] PROGMEM = R"=====(
%s<br><input type="text" name="%s" value="%s" minlength="1"><br><br>
)=====";

const char form_text_field_int[] PROGMEM = R"=====(
%s<br><input type="text" name="%s" value="%d"><br><br>
)=====";

const char form_text_field_int_min[] PROGMEM = R"=====(
%s<br><input type="text" name="%s" value="%d" minlength="1"><br><br>
)=====";


const char form_end[] PROGMEM = R"=====(
</form>
)=====";

const char menu_entry[] PROGMEM = R"=====(
<form action="%s"><input type="submit" value="%s" %s></form><br>
)=====";

const char menu_fw_option[] PROGMEM = R"=====(
<button name="fw" value="%s">%s</button><br><br>
)=====";

const char menu_entry_check_restart[] PROGMEM = R"=====(
onSubmit="if(!confirm(\'Are you sure you wish to restart the device?\')){return false;}"
)=====";

const char menu_entry_check_erase[] PROGMEM = R"=====(
onSubmit="if(!confirm(\'Are you sure you wish to erase all settings?\')){return false;}"
)=====";

const char menu_entry_check_update[] PROGMEM = R"=====(
onSubmit="if(!confirm(\'Are you sure you wish to update the firmware?\')){return false;}"
)=====";

const char littlefs_fail[] PROGMEM = R"=====(
LittleFS failure!
)=====";

const char file_write_fail[] PROGMEM = R"=====(
File write failure!
)=====";

const char file_write_success[] PROGMEM = R"=====(
File write success.
)=====";
