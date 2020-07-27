//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void init_webserver()
{
    use_webserver = true;

    server.on("/", page_main);
    server.on("/generate_204", page_main);
    server.on("/fwlink", page_main);

    server.on("/wifi", cfg_page_wifi);
    server.on("/choose", cfg_page_choose);
    server.on("/sysinfo", cfg_page_sysinfo);

    server.on("/update", []() {
        server.send_P(200, "text/html", update);
        delay(200);
        ota_update();
    });

    server.on("/format", []() {
        server.send_P(200, "text/html", format);
        web_format_fs();
    });

    server.on("/restart", []() {
        server.send_P(200, "text/html", restart);
        delay(200);
        ESP.restart();
    });

    server.onNotFound([]() {
        server.send_P(404, "text/html", notfound);
    });

    server.begin();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// ##     ##    ###    #### ##    ##    ########     ###     ######   ########
// ###   ###   ## ##    ##  ###   ##    ##     ##   ## ##   ##    ##  ##
// #### ####  ##   ##   ##  ####  ##    ##     ##  ##   ##  ##        ##
// ## ### ## ##     ##  ##  ## ## ##    ########  ##     ## ##   #### ######
// ##     ## #########  ##  ##  ####    ##        ######### ##    ##  ##
// ##     ## ##     ##  ##  ##   ###    ##        ##     ## ##    ##  ##
// ##     ## ##     ## #### ##    ##    ##        ##     ##  ######   ########

void page_main()
{
    // use HTTP/1.1 Chunked response to avoid building a huge temporary string
    if (!server.chunkedResponseModeStart(200, "text/html"))
    {
        server.send(505, F("text/html"), F("HTTP1.1 required"));
        return;
    }

    char buffer[256];

    server.sendContent_P(page_header);
    server.sendContent(F("<h2>3DStarT<br>configuration</h2><br>"));

    sprintf_P(buffer, menu_entry, "/choose", "Choose next firmware", "");
    server.sendContent(buffer);

    server.sendContent_P(html_hr);

    sprintf_P(buffer, menu_entry, "/wifi", "WiFi", "");
    server.sendContent(buffer);
    sprintf_P(buffer, menu_entry, "/update", "Update firmware", menu_entry_check_update);
    server.sendContent(buffer);
    sprintf_P(buffer, menu_entry, "/format", "Erase settings", menu_entry_check_erase);
    server.sendContent(buffer);
    sprintf_P(buffer, menu_entry, "/restart", "Restart", menu_entry_check_restart);
    server.sendContent(buffer);
    sprintf_P(buffer, menu_entry, "/sysinfo", "System information", "");
    server.sendContent(buffer);

    server.sendContent_P(page_footer);
    server.chunkedResponseFinalize();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
// ##      ## #### ######## ####
// ##  ##  ##  ##  ##        ##
// ##  ##  ##  ##  ##        ##
// ##  ##  ##  ##  ######    ##
// ##  ##  ##  ##  ##        ##
// ##  ##  ##  ##  ##        ##
//  ###  ###  #### ##       ####

void cfg_page_wifi()
{
    if (server.hasArg("SSIDa"))
        strlcpy(SSIDa, server.arg("SSIDa").c_str(), sizeof(SSIDa));

    if (server.hasArg("PASSa"))
        strlcpy(PASSa, server.arg("PASSa").c_str(), sizeof(PASSa));

    if (server.hasArg("SSIDb"))
        strlcpy(SSIDb, server.arg("SSIDb").c_str(), sizeof(SSIDb));

    if (server.hasArg("PASSb"))
        strlcpy(PASSb, server.arg("PASSb").c_str(), sizeof(PASSb));

    ///////////
    yield();
    ///////////

    // use HTTP/1.1 Chunked response to avoid building a huge temporary string
    if (!server.chunkedResponseModeStart(200, "text/html"))
    {
        server.send(505, F("text/html"), F("HTTP1.1 required"));
        return;
    }

    server.sendContent_P(page_header);

    int i = 0;
    int n = WiFi.scanComplete();

    if (n >= 0)
    {
        server.sendContent_P(form_start);
        for (i = 0; i < n; i++)
        {
            server.sendContent(F("<input type='submit' name='SSIDa' value='"));
            server.sendContent(String() + WiFi.SSID(i) + "'> - ch." + WiFi.channel(i) + " (" + WiFi.RSSI(i) + " dBm)<br>");
        }
        server.sendContent_P(form_end);
        server.sendContent_P(html_hr);
    }

    char buffer[256];

    server.sendContent_P(form_start);

    sprintf_P(buffer, form_text_field_string, "SSIDa", "SSIDa", SSIDa);
    server.sendContent(buffer);

    sprintf_P(buffer, form_text_field_string, "PASSa", "PASSa", PASSa);
    server.sendContent(buffer);

    sprintf_P(buffer, form_text_field_string, "SSIDb", "SSIDb", SSIDb);
    server.sendContent(buffer);

    sprintf_P(buffer, form_text_field_string, "PASSb", "PASSb", PASSb);
    server.sendContent(buffer);

    server.sendContent_P(form_buttons);

    if (server.hasArg("save"))
    {
        server.sendContent(F("<hr>Save to config file: "));
        server.sendContent(save_wifi());
    }

    server.sendContent_P(page_footer);
    server.chunkedResponseFinalize();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//  ######  ##     ##  #######   #######   ######  ########
// ##    ## ##     ## ##     ## ##     ## ##    ## ##
// ##       ##     ## ##     ## ##     ## ##       ##
// ##       ######### ##     ## ##     ##  ######  ######
// ##       ##     ## ##     ## ##     ##       ## ##
// ##    ## ##     ## ##     ## ##     ## ##    ## ##
//  ######  ##     ##  #######   #######   ######  ########

void cfg_page_choose()
{
    char FW[33] = {0};

    if (server.hasArg("fw"))
        strlcpy(FW, server.arg("fw").c_str(), sizeof(FW));

    ///////////
    yield();
    ///////////

    // use HTTP/1.1 Chunked response to avoid building a huge temporary string
    if (!server.chunkedResponseModeStart(200, "text/html"))
    {
        server.send(505, F("text/html"), F("HTTP1.1 required"));
        return;
    }

    char buffer[256];

    server.sendContent_P(page_header);

    server.sendContent(F("<h2>Choose your next firmware</h2>"));
    if (use_dns)
        server.sendContent(F("<h2>but first connect to a WiFi network!</h2>"));

    server.sendContent_P(form_start);

    sprintf_P(buffer, menu_fw_option, "ESPbutton", "ESPbutton");
    server.sendContent(buffer);

    sprintf_P(buffer, menu_fw_option, "ESPbutton_SSL", "ESPbutton SSL");
    server.sendContent(buffer);

    server.sendContent_P(form_end);
    server.sendContent_P(form_button_back);

    server.sendContent_P(page_footer);
    server.chunkedResponseFinalize();

    if (strlen(FW) > 1)
    {
        char url[128];

        sprintf(url, "http://%s?t=%s&v=0.00", update_url, FW);

        ESPhttpUpdate.update(net, url);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//  ######  ##    ##  ######  #### ##    ## ########  #######
// ##    ##  ##  ##  ##    ##  ##  ###   ## ##       ##     ##
// ##         ####   ##        ##  ####  ## ##       ##     ##
//  ######     ##     ######   ##  ## ## ## ######   ##     ##
//       ##    ##          ##  ##  ##  #### ##       ##     ##
// ##    ##    ##    ##    ##  ##  ##   ### ##       ##     ##
//  ######     ##     ######  #### ##    ## ##        #######

void cfg_page_sysinfo()
{
    // use HTTP/1.1 Chunked response to avoid building a huge temporary string
    if (!server.chunkedResponseModeStart(200, "text/html"))
    {
        server.send(505, F("text/html"), F("HTTP1.1 required"));
        return;
    }

    char buffer[256] = {0};

    server.sendContent_P(page_header);
    server.sendContent_P(html_table_i);

    ////////////////////////

    sprintf_P(buffer, PSTR("<td>FW name</td><td>%s</td>"), FW_NAME);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>FW version</td><td>%.2f</td>"), VERSION);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>FW size</td><td>%.2f KB</td>"), ESP.getSketchSize() / 1024.0);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>free flash size</td><td>%.2f KB</td>"), ESP.getFreeSketchSpace() / 1024.0);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>FW MD5</td><td>%s</td>"), ESP.getSketchMD5().c_str());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>FW CRC</td><td>%s</td>"), ESP.checkFlashCRC() ? "OK" : "ERROR!!!");
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Core version</td><td>%s</td>"), ESP.getCoreVersion().c_str());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>SDK version</td><td>%s</td>"), ESP.getSdkVersion());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    ////////////////////////
    server.sendContent_P(html_table_tr_hr);
    ////////////////////////

    sprintf_P(buffer, PSTR("<td>Reset reason</td><td>%s</td>"), ESP.getResetReason().c_str());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Free Heap</td><td>%.2f KB</td>"), ESP.getFreeHeap() / 1024.0);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Max Free Block</td><td>%.2f KB</td>"), ESP.getMaxFreeBlockSize() / 1024.0);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Heap Fragmentation</td><td>%d%%</td>"), ESP.getHeapFragmentation());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    ////////////////////////
    server.sendContent_P(html_table_tr_hr);
    ////////////////////////

    sprintf_P(buffer, PSTR("<td>ESP Chip ID</td><td>%08X</td>"), ESP.getChipId());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>CPU frequency</td><td>%d MHz</td>"), ESP.getCpuFreqMHz());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Flash Chip ID</td><td>%08X</td>"), ESP.getFlashChipId());
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Flash frequency</td><td>%d MHz</td>"), ESP.getFlashChipSpeed() / 1000000);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Used flash size</td><td>%d KB</td>"), ESP.getFlashChipSize() / 1024);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    sprintf_P(buffer, PSTR("<td>Flash size</td><td>%d KB</td>"), ESP.getFlashChipRealSize() / 1024);
    server.sendContent(buffer);
    server.sendContent_P(html_table_tr);

    ////////////////////////

    server.sendContent_P(html_table_s);

    server.sendContent(F("<br><br><form action='/'><input type='submit' value='Main menu'></form>"));
    server.sendContent_P(page_footer);
    server.chunkedResponseFinalize();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
