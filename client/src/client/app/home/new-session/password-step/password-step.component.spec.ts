import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { PasswordStepModule } from './password-step.module';

export function main() {
   describe('Password step component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [PasswordStepModule]
      });
    });

    it('should have an input',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let passwordStepDOMElement =
              fixture.debugElement.children[0].nativeElement;

            expect(passwordStepDOMElement.querySelectorAll('input').length)
              .toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<password-step></password-step>'
})
class TestComponent {}
