import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../shared/shared.module';
import { StartStepComponent } from './start-step.component';
import { SnifferClientService } from './../../shared/sniffer-client/index';
import { SnifferConfigurationService } from './../../shared/sniffer-configuration/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [StartStepComponent],
  exports: [StartStepComponent],
  providers: [SnifferConfigurationService, SnifferClientService]
})
export class StartStepModule { }
