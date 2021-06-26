import { ComponentFixture, TestBed } from '@angular/core/testing';

import { CoffeeAddComponent } from './coffee-add.component';

describe('CoffeeAddComponent', () => {
  let component: CoffeeAddComponent;
  let fixture: ComponentFixture<CoffeeAddComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ CoffeeAddComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(CoffeeAddComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
