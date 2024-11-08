#include <avr/io.h>

FUSES = {
    .WDTCFG = WDT_PERIOD_OFF_gc | WDT_WINDOW_OFF_gc,
    .BODCFG = BOD_SLEEP_DIS_gc | BOD_ACTIVE_DIS_gc | BOD_SAMPFREQ_32HZ_gc | BOD_LVL_BODLEVEL0_gc,
    .OSCCFG = CLKSEL_OSCHF_gc,
    .SYSCFG0 = CRCSRC_NOCRC_gc | CRCSEL_CRC16_gc | UPDIPINCFG_UPDI_gc | RSTPINCFG_GPIO_gc,
    .SYSCFG1 = MVSYSCFG_SINGLE_gc | SUT_0MS_gc,
    .CODESIZE = 0,
    .BOOTSIZE = 0

};
