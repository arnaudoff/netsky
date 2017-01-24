import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../shared/shared.module';

import { PasswordStepModule } from './password-step/password-step.module';
import { InterfaceStepModule } from './interface-step/interface-step.module';
import { FilterStepModule } from './filter-step/filter-step.module';
import { StartStepModule } from './start-step/start-step.module';

import { NewSessionComponent } from './new-session.component';

@NgModule({
  imports: [
    CommonModule, SharedModule, PasswordStepModule, InterfaceStepModule,
    FilterStepModule, StartStepModule
  ],
  declarations: [NewSessionComponent],
  exports: [NewSessionComponent]
})
export class NewSessionModule {}
