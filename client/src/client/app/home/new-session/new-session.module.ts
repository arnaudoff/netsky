import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../shared/shared.module';

import { InterfaceStepModule } from './interface-step/interface-step.module';
import { FilterStepModule } from './filter-step/filter-step.module';
import { StartStepModule } from './start-step/start-step.module';
import { NewSessionRoutingModule } from './new-session-routing.module';

import { NewSessionComponent } from './new-session.component';

@NgModule({
  imports: [
    CommonModule, SharedModule, InterfaceStepModule, FilterStepModule,
    StartStepModule, NewSessionRoutingModule
  ],
  declarations: [NewSessionComponent],
  exports: [NewSessionComponent]
})
export class NewSessionModule {}
