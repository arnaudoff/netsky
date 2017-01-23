import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../../shared/shared.module';
import { SnifferService } from './../../../shared/sniffer/index';

import { StartStepComponent } from './start-step.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [StartStepComponent],
  exports: [StartStepComponent],
  providers: [SnifferService]
})
export class StartStepModule { }
