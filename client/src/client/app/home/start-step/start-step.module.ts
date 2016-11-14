import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from './../../shared/shared.module';
import { StartStepComponent } from './start-step.component';
import { SnifferClientService } from './../../shared/sniffer-client/index';
import { SnifferConfigBuilderService } from './../../shared/sniffer-config-builder/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [StartStepComponent],
  exports: [StartStepComponent],
  providers: [SnifferConfigBuilderService, SnifferClientService]
})

export class StartStepModule { }
