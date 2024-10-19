#import <Cocoa/Cocoa.h>

const char* VACA_OSX_openFileDialog(void) 
{
    @autoreleasepool 
    {
        NSOpenPanel* panel = [NSOpenPanel openPanel];
        [panel setCanChooseFiles:YES];
        [panel setAllowsMultipleSelection:NO];
        [panel setCanChooseDirectories:NO];

        if ([panel runModal] == NSModalResponseOK)
        {
            NSURL* chosenFile = [[panel URLs] objectAtIndex:0];
            return [chosenFile.path UTF8String];
        }
    }
    return NULL;
}
