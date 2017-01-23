import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { SharedModule } from './../../../shared/shared.module';
import { PasswordStepComponent } from './password-step.component';

@NgModule({
  imports: [CommonModule, SharedModule],
  declarations: [PasswordStepComponent],
  exports: [PasswordStepComponent]
})
export class PasswordStepModule { }
