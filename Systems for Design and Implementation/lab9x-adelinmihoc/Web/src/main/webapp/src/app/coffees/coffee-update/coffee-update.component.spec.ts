import { ComponentFixture, TestBed } from '@angular/core/testing';

import { CoffeeUpdateComponent } from './coffee-update.component';

describe('CoffeeUpdateComponent', () => {
  let component: CoffeeUpdateComponent;
  let fixture: ComponentFixture<CoffeeUpdateComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ CoffeeUpdateComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(CoffeeUpdateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
