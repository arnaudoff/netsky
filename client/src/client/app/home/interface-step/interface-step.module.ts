import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from './../../shared/shared.module';
import { InterfaceStepComponent } from './interface-step.component';
import { SnifferConfigBuilderService } from './../../shared/sniffer-config-builder/index';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [InterfaceStepComponent],
  exports: [InterfaceStepComponent],
  providers: [SnifferConfigBuilderService]
})

export class InterfaceStepModule { }