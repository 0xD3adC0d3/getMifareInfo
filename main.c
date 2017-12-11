#include <stdlib.h>
#include <string.h>
#include <nfc/nfc.h>
#include <freefare.h>

int main(){
	nfc_device *pnd;
	MifareTag *tags;
	nfc_context *context = NULL;
	nfc_init(&context);
	if (context == NULL) {
		printf("Unable to init libnfc\n");
		exit(EXIT_FAILURE);
	}
	pnd = nfc_open(context, NULL);
	if (pnd == NULL) {
		printf("ERROR: %s\n", "Unable to open NFC device.");
		exit(EXIT_FAILURE);
	}
	printf("NFC reader: %s opened\n", nfc_device_get_name(pnd));
	tags = freefare_get_tags(pnd);
	if (tags[0] == NULL) {
		printf("No Mifare classic tag found\n");
	} else {
		switch(freefare_get_tag_type(tags[0])) {
			case CLASSIC_1K:
				printf("Mifare 1k (S50) UID: %s\n", freefare_get_tag_uid(tags[0]));
				break;
			case CLASSIC_4K:
				printf("Mifare 4k (S70) UID: %s\n", freefare_get_tag_uid(tags[0]));
				break;
			default:
				printf("Other ISO14443A tag UID: %s\n", freefare_get_tag_uid(tags[0]));
		}
		printf ("Found (firendly name) : %s\n", freefare_get_tag_friendly_name(tags[0]));
	}
	freefare_free_tags(tags);
	nfc_close(pnd);
	nfc_exit(context);
	exit(EXIT_SUCCESS);
}
