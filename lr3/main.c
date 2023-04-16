#define CHIP_6713 1
#include <dsk6713.h>
#include <dsk6713_aic23.h>


/* Codec configuration settings */
DSK6713_AIC23_Config config = {
	0x0017, // 0 DSK6713_AIC23_LEFTINVOL Left line inputchannel volume
	0x0017, // 1 DSK6713_AIC23_RIGHTINVOL Right line inputchannel volume
	0x00d8, // 2 DSK6713_AIC23_LEFTHPVOL Left channelheadphone volume
	0x00d8, // 3 DSK6713_AIC23_RIGHTHPVOL Right channelheadphone volume
	0x0011, // 4 DSK6713_AIC23_ANAPATH Analog audio pathcontrol
	0x0000, // 5 DSK6713_AIC23_DIGPATH Digital audio pathcontrol
	0x0000, // 6 DSK6713_AIC23_POWERDOWN Power down control
	0x0043, // 7 DSK6713_AIC23_DIGIF Digital audiointerface format
	0x0001,  //  8  DSK6713_AIC23_SAMPLERATE  Sample  ratecontrol
	0x0001 // 9 DSK6713_AIC23_DIGACT Digital interfaceactivation
};
interrupt void c_int11();
void initIRQ(int IRQ_id);
void main()
{
	DSK6713_AIC23_CodecHandle hCodec;
	/* Initialize the board support library, must be called
	first */
	DSK6713_init();
	/* Start the codec */
	hCodec = DSK6713_AIC23_openCodec(0, &config);
	DSK6713_AIC23_setFreq(hCodec,1);
	// Configure buffered serial ports for 32 bit operation (L+R in one read/write)
	MCBSP_FSETS(SPCR1, RINTM, FRM);
	MCBSP_FSETS(SPCR1, XINTM, FRM);
	MCBSP_FSETS(RCR1, RWDLEN1, 32BIT);
	MCBSP_FSETS(XCR1, XWDLEN1, 32BIT);
	initIRQ(11);
	while(1);
	/* Close the codec */
	DSK6713_AIC23_closeCodec(hCodec);
}

interrupt void c_int11()
{
	Uint32 temp;
	temp = MCBSP_read(DSK6713_AIC23_DATAHANDLE); // read L+R	channels
	MCBSP_write(DSK6713_AIC23_DATAHANDLE,temp); // write L+R	channels
}
void initIRQ(int IRQ_id)
{
// Globally disables interrupts by clearing the GIE bitof the CSR register.
IRQ_globalDisable();
// map the event ID associated with the handling of McBSP1
// with the physical interrupt IRQ_id
IRQ_map(IRQ_EVT_RINT1, IRQ_id);
// resets the event ID by disabling then clearing it.
IRQ_reset(IRQ_EVT_RINT1);
// Globally enables interrupt. This function globallyenables
// interrupts by setting thQe GIE bit of the CSR register to 1.
IRQ_globalEnable();
// Enables the NMI interrupt event
IRQ_nmiEnable();
// enable the specified event
IRQ_enable(IRQ_EVT_RINT1);
}